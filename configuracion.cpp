/*
 * configuracion.cpp
 *
 *  Created on: May 13, 2018
 *      Author: daniel
 */

#include "configuracion.hpp"


void ConfigADC()
{
    ADC14->CTL0 = ADC14_CTL0_SSEL__MCLK | ADC14_CTL0_PDIV__32
                | ADC14_CTL0_DIV__2 | ADC14_CTL0_SHT0__64
                | ADC14_CTL0_SHS_0 | ADC14_CTL0_SHP
                | ADC14_CTL0_CONSEQ_1 | ADC14_CTL0_MSC
                | ADC14_CTL0_ON ;


    /**
     * Tension de referencia VRSel:
     *      V+ = AVCC (3.3 V) y V- = AVSS (0 V)
     * INput CHannel = A14 (P6.1) x
     *                 A13 (P4.0) y
     *                 A11 (P4.2) z
     */

    ADC14->MCTL[0] = ADC14_MCTLN_INCH_14 | ADC14_MCTLN_VRSEL_0;
    ADC14->MCTL[1] = ADC14_MCTLN_INCH_13 | ADC14_MCTLN_VRSEL_0;
    ADC14->MCTL[2] = ADC14_MCTLN_INCH_11 | ADC14_MCTLN_VRSEL_0
                        | ADC14_MCTLN_EOS; // Conversion acaba en ADC14-MEM[2]

    // Habilitar conversion
    ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_ENC;

    // Habilitar interrupciones de MEM2
    ADC14->IER0 = ADC14_IER0_IE2;

    NVIC_SetPriority(ADC14_IRQn,1);
    NVIC_EnableIRQ(ADC14_IRQn);
}

void ConfigAccel()
{
    P6->DIR &= ~BIT1;
    P4->DIR &= ~(BIT0 | BIT2);
}
