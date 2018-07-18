/*
 * FrameBuffer.cpp
 *
 *  Created on: Jul 17, 2018
 *      Author: daniel
 */

#include <FrameBuffer.hpp>

FrameBuffer::FrameBuffer()
{
    m_f8pFgFrame = &m_f8Frame0;
    m_f8pBgFrame = &m_f8Frame1;

    ClearFrame(&m_f8Frame0);
    ClearFrame(&m_f8Frame1);

}

FrameBuffer::~FrameBuffer()
{
    // TODO Auto-generated destructor stub
}

uint8_t FrameBuffer::setup()
{
    // - Initializes display
    Crystalfontz128x128_Init();

    // - Sets screen orientation as UP
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    // - Initializes graphics context
    Graphics_initContext(&m_stContext, &g_sCrystalfontz128x128);
    Graphics_setBackgroundColor(&m_stContext, GRAPHICS_COLOR_WHITE);
    Graphics_setForegroundColor(&m_stContext, GRAPHICS_COLOR_BLACK);

    // - Clears Display
    Graphics_clearDisplay(&m_stContext);


    m_iState = Reset;


    return(NO_ERR);
}

uint8_t FrameBuffer::run()
{
    ReadMsgs();

    switch(m_iState) {
    case Reset: {
        m_u16Row = 0;
        m_iState = NotifyCompositor;
        break;
    }
    case Drawing: {
        if (DrawFrame()) {
            m_u16Row = 0;
            if (m_bNextFrameReady) {
                m_bNextFrameReady = false;
                SwitchFrame();
                m_iState = NotifyCompositor;
            } else {
                m_iState = Drawing;
            }
        }
        break;
    }
    case NotifyCompositor: {

        if (SendBGFrame()) {
            m_iState = Drawing;
        }
        break;
    }
    default:
        m_iState = Reset;
        break;
    }


    return(NO_ERR);
}

void FrameBuffer::ReadMsgs()
{
    st_Message l_stMensaje = getMessage(m_u8TaskID);
    if (l_stMensaje.bMessageValid && l_stMensaje.u8MessageCode == i16ScalarMessage){
        if (l_stMensaje.u32MessageData == FRAME_READY) {
            m_bNextFrameReady = true;
        }
    }
}

void FrameBuffer::ClearFrame(frame8p_t f)
{
    for (int y = 0; y < FR_YS; y++) {
        for (int x = 0; x < FR_XS; x++){
            f->pixels[y * FR_XS + x] = 0;
        }
    }
}

bool FrameBuffer::DrawFrame()
{
    DrawRow();
    m_u16Row++;
    if (m_u16Row > FR_YS) {
        return true;
    }
    return false;

}

void FrameBuffer::DrawRow()
{
    for (int16_t x = 0; x < FR_XS; x++) {
        Graphics_setForegroundColor(&m_stContext, g_pColorTable[m_f8pFgFrame->pixels[FR_XS * m_u16Row + x]]);
        //Graphics_drawHorizontalLineOnDisplay(m_stContext.display, x, x, m_u16Row, m_stContext.foreground);
        Graphics_drawLineH(&m_stContext, x, x+1, m_u16Row);
    }
}

void FrameBuffer::SwitchFrame()
{
    // Intercambiar los frame buffers
    frame8p_t tmp = m_f8pFgFrame;
    m_f8pFgFrame = m_f8pBgFrame;
    m_f8pBgFrame = tmp;

}

bool FrameBuffer::SendBGFrame() {
    // Alertar al compositor del nuevo buffer
    st_Message l_stMensaje;
    l_stMensaje.bMessageValid = true;
    l_stMensaje.u8SourceID = m_u8TaskID;
    l_stMensaje.u8DestinationID = m_u8CompositorTask;
    l_stMensaje.u8MessageCode = pointerMessage;
    l_stMensaje.u32MessageData = NEW_FB;
    l_stMensaje.pPayload = (uint8_t*)m_f8pBgFrame;
    return sendMessage(l_stMensaje);

}
