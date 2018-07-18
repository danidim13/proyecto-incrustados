/*
 * GameTask.cpp
 *
 *  Created on: Jul 18, 2018
 *      Author: daniel
 */

#include <GameTask.hpp>

GameTask::GameTask()
{
    // TODO Auto-generated constructor stub

}

GameTask::~GameTask()
{
    // TODO Auto-generated destructor stub
}

uint8_t GameTask::setup()
{
    m_fXforce = 0;
    m_fYforce = 0;
    m_fForceScale = 1.0;
    m_oGame.SetGravity(m_fXforce, m_fYforce);
    return NO_ERR;
}

uint8_t GameTask::run()
{

    if (GetXYForce()) {
        m_oGame.SetGravity(m_fXforce, m_fYforce);
    }
    m_oGame.Step();
    return NO_ERR;
}


Entity* GameTask::GetEntities(int* i_iElem)
{
    *i_iElem = 1;
    return &m_oGame.bolita;
}


bool GameTask::GetXYForce()
{
    st_Message l_stMensaje = getMessage(m_u8TaskID);
    if (l_stMensaje.bMessageValid && l_stMensaje.u8MessageCode == i16VectorMessage ) {
        int len = l_stMensaje.u32MessageData;
        if (len != 2){
            return false;
        }
        float32_t * data = (float32_t*) l_stMensaje.pPayload;
        m_fXforce = -data[0] * m_fForceScale;
        m_fYforce = data[1] * m_fForceScale;
        return true;
    }
    return false;
}
