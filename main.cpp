#include "msp.h"
#include "main.hpp"
#include "Scheduler.hpp"
#include "Task.hpp"
#include "Display.hpp"
#include "configuracion.hpp"
#include "AngleFinder.hpp"
#include "Compositor.hpp"
#include "GameTask.hpp"
#include <stdlib.h>
#include <time.h>

// ##########################
// Global/Static declarations
// ##########################
uint8_t Task::m_u8NextTaskID = 0; // - Init task ID

volatile static uint64_t g_SystemTicks = 0; // - The system counter.
Mailbox* g_Mailbox = Mailbox::getMailbox();
Scheduler g_MainScheduler; // - Instantiate a Scheduler

// #########################
//          MAIN
// #########################
void main(void)
{
    unsigned int seed = 0xc0ffee00;

    srand(seed);

    AngleFinder AngleTask;
    GameTask gameTask;
    AngleTask.m_u8DrawTask = AngleTask.m_u8TaskID;
    AngleTask.m_u8DrawTask = gameTask.m_u8TaskID;

    //FrameBuffer fbTask;
    Compositor compTask;

    int i = 0;
    Entity* entities = gameTask.GetEntities(&i);

    compTask.SetEntities(entities, i);

    //fbTask.m_u8CompositorTask = compTask.m_u8TaskID;
    //compTask.m_u8RenderTask = fbTask.m_u8TaskID;



    // - Run the overall setup function for the system
    Setup();
    // - Attach the Tasks to the Scheduler;
    //g_MainScheduler.attach(&BlueLED,TaskType_Periodic, TaskActiveTrue,1000);
    //g_MainScheduler.attach(&GreenLED, TaskType_Periodic,TaskActiveTrue,750);

    // La pantalla se refresca a Aprox 30 Hz
    //g_MainScheduler.attach(&Pantalla, TaskType_Always,TaskActiveFalse,1);

    g_MainScheduler.attach(&compTask, TaskType_Periodic,TaskActiveTrue, 2);

    // Se calcula un nuevo angulo aprox cada 75 ms.
    g_MainScheduler.attach(&AngleTask, TaskType_Periodic, TaskActiveTrue, 200);
    g_MainScheduler.attach(&gameTask, TaskType_Periodic, TaskActiveTrue, 100);
    g_MainScheduler.m_u8ADCTask = AngleTask.m_u8TaskID;

    // - Run the Setup for the scheduler and all tasks
    g_MainScheduler.setup();

    // - Main Loop
    while(1)
    {
        __wfe(); // Wait for Event
        if(g_SystemTicks != g_MainScheduler.m_u64ticks)
        {
            //- Only execute the tasks if one tick has passed.
            g_MainScheduler.m_u64ticks = g_SystemTicks;
            g_MainScheduler.run();
        }
    }
}

// **********************************
// Setup function for the application
// @input - none
// @output - none
// **********************************
void Setup(void)
{
    // ****************************
    //         DEVICE CONFIG
    // ****************************
    // - Disable WDT
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    // ****************************
    //         PORT CONFIG
    // ****************************
    // - P1.0 is connected to the Red LED
    // - This is the heart beat indicator.
    P1->DIR |= BIT0; //Red LED

    // ****************************
    //       TIMER CONFIG
    // ****************************
    // - Configure Timer32_1  with MCLK (48Mhz), Division by 1, Enable the interrupt, Periodic Mode
    // - Enable the interrupt in the NVIC
    // - Start the timer in UP mode.
    // - Re-enable interrupts
    TIMER32_1->LOAD = TIMER32_COUNT; //~1ms ---> a 3Mhz
    TIMER32_1->CONTROL = TIMER32_CONTROL_SIZE | TIMER32_CONTROL_PRESCALE_0 | TIMER32_CONTROL_MODE | TIMER32_CONTROL_IE | TIMER32_CONTROL_ENABLE;
    NVIC_SetPriority(T32_INT1_IRQn,1);
    NVIC_EnableIRQ(T32_INT1_IRQn);



    ConfigAccel();
    ConfigADC();

    __enable_irq();

    return;
}

extern "C"
{
    // - Handle the Timer32 Interrupt
    void T32_INT1_IRQHandler(void)
    {
        TIMER32_1->INTCLR = 0U;
        P1->OUT ^= BIT0; // - Toggle the heart beat indicator (1ms)
        g_SystemTicks++;
        return;
    }

    void ADC14_IRQHandler(void)
    {
        __disable_irq();

        ADC14->CLRIFGR0 = ADC14_CLRIFGR0_CLRIFG2 | ADC14_CLRIFGR0_CLRIFG1 | ADC14_CLRIFGR0_CLRIFG0;

        int16_t setpoint = 8192;
        int16_t x, y, z;
        x = setpoint - ADC14->MEM[0];
        y = setpoint - ADC14->MEM[1];
        z = setpoint - ADC14->MEM[2];


        g_MainScheduler.ADCHandler(x, y, z);

        __enable_irq();
    }
}
