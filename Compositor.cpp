/*
 * Compositor.cpp
 *
 *  Created on: Jul 18, 2018
 *      Author: daniel
 */

#include <Compositor.hpp>

Compositor::Compositor()
{
    m_iBgX = 0;
    m_iBgY = 0;
    m_iSpr = 0;
}

Compositor::~Compositor()
{
    // TODO Auto-generated destructor stub
}

uint8_t Compositor::setup()
{
    m_iState = Reset;

    Crystalfontz128x128_Init();

    // - Sets screen orientation as UP
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    // - Initializes graphics context
    Graphics_initContext(&m_stContext, &g_sCrystalfontz128x128);
    Graphics_setBackgroundColor(&m_stContext, GRAPHICS_COLOR_WHITE);
    Graphics_setForegroundColor(&m_stContext, GRAPHICS_COLOR_BLACK);

    // - Clears Display
    Graphics_clearDisplay(&m_stContext);

    return NO_ERR;
}

uint8_t Compositor::run()
{
    switch(m_iState){
    case Reset: {
        m_iState = DrawingBg;
        m_iBgX = 0;
        m_iBgY = 0;
        break;
    }
    case DrawingBg: {
        if (DrawBackgroundStep()) {
            m_iState = DrawingSpr;
            m_iSpr = 0;
        }
        break;
    }
    case DrawingSpr: {
        m_iState = Finished;
        break;
    }
    case Finished: {
        m_iState = DrawingBg;
        m_iBgX = 0;
        m_iBgY = 0;
        break;
    }
    default: {
        m_iState = Reset;
        break;
    }
    }
    return NO_ERR;
}

/*
bool Compositor::GetFrame()
{
    return true;
    st_Message l_stMensaje = getMessage(m_u8TaskID);
    if (l_stMensaje.bMessageValid && l_stMensaje.u8MessageCode == pointerMessage){
        if (l_stMensaje.u32MessageData == NEW_FB) {
            //m_f8pFrame = (frame8p_t)l_stMensaje.pPayload;
            return true;
        }
    }
    return false;
}
*/


bool Compositor::DrawBackgroundStep()
{
    // Dibuja un rectangulo en el frame buffer del color que se guardo
    int y_s = m_iBgY * CELL_Y;
    int x_s = m_iBgX * CELL_X;

    int16_t cell = m_stBackgroud.grid[m_iBgY*GRID_LX + m_iBgX];
    // Pintar la celda
    struct Graphics_Rectangle rect;
    rect.xMin = x_s;
    rect.yMin = y_s;
    rect.xMax = x_s + CELL_X-1;
    rect.yMax = y_s + CELL_Y-1;


    //int32_t bgColor = g_pColorTable[ cell & COLOR_BG ];
    //int32_t fgColor = g_pColorTable[ (cell & COLOR_FG) >> COLOR_BITS ];
    int32_t bgColor = m_stBackgroud.bg;
    int32_t fgColor = m_stBackgroud.fg;


    Graphics_setForegroundColor(&m_stContext, fgColor);

    if (cell & TOP_B) {
        rect.yMin++;
        Graphics_drawLineH(&m_stContext, x_s, x_s + CELL_X-1, y_s);
    }
    if (cell & BOT_B) {
        rect.yMax--;
        Graphics_drawLineH(&m_stContext, x_s, x_s + CELL_X-1, y_s + CELL_Y-1);
    }
    if (cell & RIGHT_B) {
        rect.xMax--;
        Graphics_drawLineV(&m_stContext, x_s + CELL_X-1, y_s, y_s + CELL_Y-1);
    }
    if (cell & LEFT_B) {
        rect.xMin++ ;
        Graphics_drawLineV(&m_stContext, x_s, y_s, y_s + CELL_Y-1);
    }

    Graphics_setForegroundColor(&m_stContext, bgColor);
    Graphics_fillRectangle(&m_stContext, &rect);



    m_iBgX++;
    if (m_iBgX >= GRID_LX){
        m_iBgY++;
        m_iBgX = 0;
    }
    // Terminamos
    if (m_iBgY >= GRID_LY) {
        return true;
    }

    return false;
}

/*
bool Compositor::NotifyRenderer()
{
    return true;
    st_Message l_stMensaje;
    l_stMensaje.bMessageValid = true;
    l_stMensaje.u8SourceID = m_u8TaskID;
    l_stMensaje.u8DestinationID = m_u8RenderTask;
    l_stMensaje.u8MessageCode = i16ScalarMessage;
    l_stMensaje.u32MessageData = FRAME_READY;
    return sendMessage(l_stMensaje);

}
*/
