/*
 * AngleFinder.cpp
 *
 *  Created on: May 13, 2018
 *      Author: daniel
 */

#include <AngleFinder.hpp>
#include <math.h>

AngleFinder::AngleFinder()
{
    m_i16LastY = 128/2;
    m_bFirstTime = true;
    // TODO Auto-generated constructor stub

}

AngleFinder::~AngleFinder()
{
    // TODO Auto-generated destructor stub
}

uint8_t AngleFinder::run()
{

    if (GetGravityVec()){

        float32_t l_fGrav2, l_fGravNorm;
        arm_dot_prod_f32(m_fGravityVec, m_fGravityVec, 3, &l_fGrav2);
        arm_sqrt_f32(l_fGrav2, &l_fGravNorm);

        float32_t l_fSin = m_fGravityVec[2]/l_fGravNorm;

        m_fTheta = asinf(l_fSin);

        int16_t l_i16Height = (int16_t) (64*(1 + l_fSin));
        SendHorizon(l_i16Height);

        // Activar la pantalla cuando se tenga la primera medición.
        //if (m_bFirstTime){
        //    // Si el mensaje se manda con éxito
        //    m_bFirstTime = !ActivateDisplay();
        //}

        this->m_i16LastY = 128/2;

        // Empezar conversión
        ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_SC;
    }
    return NO_ERR;
}
bool AngleFinder::ActivateDisplay()
{
    st_Message l_stMensaje;
    l_stMensaje.bMessageValid = true;
    l_stMensaje.u8SourceID = m_u8DrawTask;
    l_stMensaje.u8DestinationID = SCHED_ID;
    l_stMensaje.u32MessageData = 1;
    l_stMensaje.u8MessageCode = setTaskActive;
    return sendMessage(l_stMensaje);
}
bool AngleFinder::SendHorizon(int16_t i_i16Horizon)
{
    if (m_u8DrawTask == m_u8TaskID)
        return true;

    st_Message l_stMensaje;
    l_stMensaje.bMessageValid = true;
    l_stMensaje.u8SourceID = m_u8TaskID;
    l_stMensaje.u8DestinationID = m_u8DrawTask;
    l_stMensaje.u32MessageData = i_i16Horizon;
    l_stMensaje.u8MessageCode = i16ScalarMessage;
    return sendMessage(l_stMensaje);
}

bool AngleFinder::GetGravityVec()
{
    st_Message l_stMensaje = getMessage(m_u8TaskID);
    if (l_stMensaje.bMessageValid && l_stMensaje.u8MessageCode == i16VectorMessage){
        int len = l_stMensaje.u32MessageData;
        int16_t *data = (int16_t *)l_stMensaje.pPayload;
        if (len != 3) {
            return false;
        }
        for (int i = 0; i < len; i++) {
            this->m_fGravityVec[i] = (float32_t) data[i];
        }
        return true;
    } else {
        return false;
    }
}
uint8_t AngleFinder::setup()
{
    return NO_ERR;

}


