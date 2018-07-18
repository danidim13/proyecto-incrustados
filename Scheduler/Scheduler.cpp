#include "Scheduler.hpp"

// - Scheduler constructor
Scheduler::Scheduler()
{
    m_u8OpenSlots = static_cast<uint8_t>(NUMBER_OF_SLOTS);
    m_u8NextSlot = 0;
    m_pMailbox = Mailbox::getMailbox();
    for(int index = 0; index < NUMBER_OF_SLOTS; index++)
    {
        m_aSchedule[index].pTask = (uintptr_t) 0; // Init to an invalid pointer
    }


    return;
}

// - The attach function, inserts the task into the schedule slots.
uint8_t Scheduler::attach(Task * i_pTask, TaskType i_enTaskType, TaskActive i_enTaskIsActive,uint64_t i_u64TickInterval)
{
    uint8_t l_ErrorCode = NO_ERR;
    st_TaskInfo l_stTaskInfo;

    l_stTaskInfo.pTask = i_pTask;
    l_stTaskInfo.bTaskIsActive = i_enTaskIsActive;
    l_stTaskInfo.u64ticks = this->m_u64ticks;
    l_stTaskInfo.u64TickInterval = 0;
	l_stTaskInfo.u64TickIntervalInitValue = i_u64TickInterval;
	l_stTaskInfo.enTaskType = i_enTaskType;

    if((m_u8OpenSlots>0) && (m_u8NextSlot < NUMBER_OF_SLOTS))
    {
        m_aSchedule[m_u8NextSlot] =  l_stTaskInfo;
        m_u8OpenSlots--;
        m_u8NextSlot++;
    }
    else
    {
        l_ErrorCode = RET_ERR;
    }
    return l_ErrorCode;
}
// - Execute the current schedule
uint8_t Scheduler::run(void)
{
    ProcessMessages();
    uint8_t l_u8NextSlot = 0U;
    Task * l_pNextTask = (uintptr_t) 0;
    uint8_t l_u8ReturnCode = NO_ERR;

    while(l_u8NextSlot < NUMBER_OF_SLOTS)
    {
        l_pNextTask = static_cast<Task *> (m_aSchedule[l_u8NextSlot].pTask);
        if(l_pNextTask != ((uintptr_t) 0))
        {
            if(m_aSchedule[l_u8NextSlot].bTaskIsActive)
            {
                // - Execute the task slot
                if(m_aSchedule[l_u8NextSlot].u64TickInterval == 0)
                {
                    l_pNextTask->run();
                }

                // - Depending on the task type, handle the tick count
                switch(m_aSchedule[l_u8NextSlot].enTaskType)
                {
                    case(TaskType_OneShot):
                        m_aSchedule[l_u8NextSlot].bTaskIsActive = TaskActiveFalse;
                        // - Intentional fall-through
                    case(TaskType_Always):
                        m_aSchedule[l_u8NextSlot].u64TickInterval = 0;
                        break;
                    case(TaskType_Periodic):
                        m_aSchedule[l_u8NextSlot].u64TickInterval ++;
                        if(m_aSchedule[l_u8NextSlot].u64TickInterval > m_aSchedule[l_u8NextSlot].u64TickIntervalInitValue)
                        {
                            m_aSchedule[l_u8NextSlot].u64TickInterval = 0;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        else
        {
            // - If we found an uninitialized slot, break from the execution loop
            break;
        }
		l_u8NextSlot++;
    }
    //CalculateNextSchedule(); // TODO

    return l_u8ReturnCode;
}
// - Execute the setup function for all tasks
uint8_t Scheduler::setup(void)
{
    int l_iNextTaskSlot = 0U;
    Task * l_pNextTask = (uintptr_t) 0;
    uint8_t l_u8ReturnCode = NO_ERR;
    // - Run the setup function for all available tasks.
    while(l_iNextTaskSlot < NUMBER_OF_SLOTS)
    {
        l_pNextTask = static_cast<Task *> (m_aSchedule[l_iNextTaskSlot].pTask);
        if(l_pNextTask != ((uintptr_t) 0))
        {
            l_pNextTask->setup();
        }
        l_iNextTaskSlot++;
    }

    // Empezar conversión
    ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_SC;

    return l_u8ReturnCode;
}

uint8_t Scheduler::CalculateNextSchedule(void)
{
    return(NO_ERR);
}
uint8_t Scheduler::SortScheduleByPriority(Task * i_pSchedule)
{
    return(NO_ERR);
}

void Scheduler::ProcessMessages()
{
    st_Message l_stMessage;
    l_stMessage = m_pMailbox->getMessage(SCHED_ID);
    while (l_stMessage.bMessageValid) {
        switch (l_stMessage.u8MessageCode) {
        case setTaskActive:
            SetTaskActive(l_stMessage.u8SourceID, l_stMessage.u32MessageData != 0);
            break;
        case setTaskOneShot:
            SetTaskOneShot(l_stMessage.u8SourceID, 0);
            break;
        case setTaskPeriodic:
            SetTaskPeriodic(l_stMessage.u8SourceID, (uint64_t)l_stMessage.u32MessageData);
            break;
        default:
            break;
        }
        l_stMessage = m_pMailbox->getMessage(SCHED_ID);
    }
}

bool Scheduler::SetTaskOneShot(uint8_t i_u8TaskID, uint64_t i_u64TickInterval)
{
    uint8_t l_u8Slot = 0;
    Task * l_pTask = (uintptr_t) 0;

    while (l_u8Slot < NUMBER_OF_SLOTS) {

        l_pTask = static_cast<Task *> (m_aSchedule[l_u8Slot].pTask);

        if ( l_pTask == (uintptr_t) 0) {
            // No se encontró el TaskID
            return false;
        } else {
            if (l_pTask->m_u8TaskID == i_u8TaskID) {
                break;
            } else {
                l_u8Slot++;
            }
        }
    }

    m_aSchedule[l_u8Slot].bTaskIsActive = TaskActiveTrue;
    m_aSchedule[l_u8Slot].u64ticks = this->m_u64ticks;
    m_aSchedule[l_u8Slot].u64TickInterval = 0;
    m_aSchedule[l_u8Slot].u64TickIntervalInitValue = i_u64TickInterval;
    m_aSchedule[l_u8Slot].enTaskType = TaskType_OneShot;
    return true;
}

bool Scheduler::SetTaskPeriodic(uint8_t i_u8TaskID, uint64_t i_u64TickInterval)
{
    uint8_t l_u8Slot = 0;
    Task * l_pTask = (uintptr_t) 0;

    while (l_u8Slot < NUMBER_OF_SLOTS) {

        l_pTask = static_cast<Task *> (m_aSchedule[l_u8Slot].pTask);

        if ( l_pTask == (uintptr_t) 0) {
            // No se encontró el TaskID
            return false;
        } else {
            if (l_pTask->m_u8TaskID == i_u8TaskID) {
                break;
            } else {
                l_u8Slot++;
            }
        }
    }

    m_aSchedule[l_u8Slot].bTaskIsActive = TaskActiveTrue;
    if (m_aSchedule[l_u8Slot].u64TickInterval > i_u64TickInterval) {
        // Solo se ejecuta inmediatamente si el tiempo que llevaba esperando
        // es mayor al nuevo periodo.
        m_aSchedule[l_u8Slot].u64TickInterval = 0;
    }
    m_aSchedule[l_u8Slot].u64TickIntervalInitValue = i_u64TickInterval;

    m_aSchedule[l_u8Slot].enTaskType = TaskType_Periodic;
    return true;
}

bool Scheduler::SetTaskActive(uint8_t i_u8TaskID, bool i_bActive)
{
    uint8_t l_u8Slot = 0;
    Task * l_pTask = (uintptr_t) 0;

    while (l_u8Slot < NUMBER_OF_SLOTS) {

        l_pTask = static_cast<Task *> (m_aSchedule[l_u8Slot].pTask);

        if ( l_pTask == (uintptr_t) 0) {
            // No se encontró el TaskID
            return false;
        } else {
            if (l_pTask->m_u8TaskID == i_u8TaskID) {
                break;
            } else {
                l_u8Slot++;
            }
        }
    }

    m_aSchedule[l_u8Slot].bTaskIsActive = i_bActive ? TaskActiveTrue : TaskActiveFalse;
    m_aSchedule[l_u8Slot].u64ticks = this->m_u64ticks;
    m_aSchedule[l_u8Slot].u64TickInterval = 0;
    return true;
}

void Scheduler::ADCHandler(int16_t i_i16X, int16_t i_i16Y, int16_t i_i16Z)
{
    st_Message l_stMensaje;
    l_stMensaje.bMessageValid = true;
    l_stMensaje.u8DestinationID = m_u8ADCTask;
    l_stMensaje.u8SourceID = SCHED_ID;
    l_stMensaje.u8MessageCode = i16VectorMessage;
    l_stMensaje.u32MessageData = 3;
    ADCResult[0] = i_i16X;
    ADCResult[1] = i_i16Y;
    ADCResult[2] = i_i16Z;
    l_stMensaje.pPayload = (uint8_t *) ADCResult;
    m_pMailbox->sendMessage(l_stMensaje);
    return;
}
