/*
 * Display.cpp
 *
 *  Created on: May 13, 2018
 *      Author: joror
 */

#include "Display.hpp"



Display::Display( )
{
    // - Esto no hace nada por el momento


    m_u16DrawIter = 0;
    m_i16HorizonHeight = -1;
    m_i8DrawDir = DD_DOWN;
}

uint8_t Display::run()
{
    GetHorizon();

    if (m_u16DrawIter == 0){
        if (m_i16NextHorizon > m_i16HorizonHeight){
            m_i8DrawDir = DD_DOWN;
            Graphics_setForegroundColor(&m_stContext, GRAPHICS_COLOR_ROYAL_BLUE);
        } else {
            m_i8DrawDir = DD_UP;
            Graphics_setForegroundColor(&m_stContext, GRAPHICS_COLOR_SIENNA);
        }
        m_i16HorizonHeight = m_i16NextHorizon;
    }
    if (m_i8DrawDir == DD_DOWN){
        DrawSectionDown();
    }
    else {
        DrawSectionUp();
    }

    //Graphics_Rectangle Rect1 = {0, 0, 128, m_i16HorizonHeight}; // - Rectangle 1 dimensions
    //Graphics_Rectangle Rect2 = {0, m_i16HorizonHeight, 128, 128}; // - Rectangle 2 dimensions

    //Graphics_setForegroundColor(&m_stContext, GRAPHICS_COLOR_ROYAL_BLUE);
    //Graphics_fillRectangle(&m_stContext, &Rect1);

    // Test code to draw a rectangles
    //Graphics_setForegroundColor(&m_stContext, GRAPHICS_COLOR_SIENNA);
    //Graphics_fillRectangle(&m_stContext, &Rect2);
    return(NO_ERR);
}

void Display::DrawSectionDown()
{
    if (m_u16DrawIter == m_i16HorizonHeight){
        Graphics_setForegroundColor(&m_stContext, GRAPHICS_COLOR_WHITE_SMOKE);
    }
    if (m_u16DrawIter == m_i16HorizonHeight+1){
        Graphics_setForegroundColor(&m_stContext, GRAPHICS_COLOR_SIENNA);
    }


    if (m_u16DrawIter == m_i16HorizonHeight - SMALL_LINE){
        DrawHalfLine(SMALL_LINE_WIDTH, m_u16DrawIter, GRAPHICS_COLOR_ROYAL_BLUE);
    } else if (m_u16DrawIter == m_i16HorizonHeight + SMALL_LINE){
        DrawHalfLine(SMALL_LINE_WIDTH, m_u16DrawIter, GRAPHICS_COLOR_SIENNA);

    } else if (m_u16DrawIter == m_i16HorizonHeight - LONG_LINE){
        DrawHalfLine(LONG_LINE_WIDTH, m_u16DrawIter, GRAPHICS_COLOR_ROYAL_BLUE);
    } else if (m_u16DrawIter == m_i16HorizonHeight + LONG_LINE){
        DrawHalfLine(LONG_LINE_WIDTH, m_u16DrawIter, GRAPHICS_COLOR_SIENNA);

    } else {
        Graphics_drawLineH(&m_stContext, 0, 128, m_u16DrawIter);
    }

    m_u16DrawIter++;

    if (m_u16DrawIter >= 128) {
        m_u16DrawIter = 0;
        Graphics_setForegroundColor(&m_stContext, GRAPHICS_COLOR_ROYAL_BLUE);
    }
    return;
}

void Display::DrawSectionUp()
{
    uint16_t l_u16IterInv = 127-m_u16DrawIter;

    if (l_u16IterInv == m_i16HorizonHeight){
        Graphics_setForegroundColor(&m_stContext, GRAPHICS_COLOR_WHITE_SMOKE);
    }
    if (l_u16IterInv == m_i16HorizonHeight-1){
        Graphics_setForegroundColor(&m_stContext, GRAPHICS_COLOR_ROYAL_BLUE);
    }

    if (l_u16IterInv == m_i16HorizonHeight-SMALL_LINE){
         DrawHalfLine(SMALL_LINE_WIDTH, l_u16IterInv, GRAPHICS_COLOR_ROYAL_BLUE);
    } else if(l_u16IterInv == m_i16HorizonHeight+SMALL_LINE){
         DrawHalfLine(SMALL_LINE_WIDTH, l_u16IterInv, GRAPHICS_COLOR_SIENNA);

    } else if (l_u16IterInv == m_i16HorizonHeight-LONG_LINE){
        DrawHalfLine(LONG_LINE_WIDTH, l_u16IterInv, GRAPHICS_COLOR_ROYAL_BLUE);
    } else if(l_u16IterInv == m_i16HorizonHeight+LONG_LINE){
        DrawHalfLine(LONG_LINE_WIDTH, l_u16IterInv, GRAPHICS_COLOR_SIENNA);

    } else {
        Graphics_drawLineH(&m_stContext, 0, 128, l_u16IterInv);
    }
    m_u16DrawIter++;

    if (m_u16DrawIter >= 128) {
        m_u16DrawIter = 0;
        Graphics_setForegroundColor(&m_stContext, GRAPHICS_COLOR_SIENNA);
    }
    return;
}

void Display::DrawHalfLine(int16_t i_i16Width, int16_t i_i16Y, int32_t i_i32Color)
{
    Graphics_drawLineH(&m_stContext, 0, (128 - i_i16Width)/2, i_i16Y);
    Graphics_setForegroundColor(&m_stContext, GRAPHICS_COLOR_WHITE_SMOKE);
    Graphics_drawLineH(&m_stContext, (128 - i_i16Width)/2, (128 + i_i16Width)/2, i_i16Y);
    Graphics_setForegroundColor(&m_stContext, i_i32Color);
    Graphics_drawLineH(&m_stContext, (128 + i_i16Width)/2, 128, i_i16Y);
}

bool Display::GetHorizon()
{
    st_Message l_stMensaje = getMessage(m_u8TaskID);
    if (l_stMensaje.bMessageValid && l_stMensaje.u8MessageCode == i16ScalarMessage){
        m_i16NextHorizon = (int16_t) l_stMensaje.u32MessageData;
        return true;
    } else {
        return false;
    }
}

uint8_t Display::setup()
{
    // ****************************
    //       DISPLAY CONFIG
    // ****************************


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

    Graphics_setForegroundColor(&m_stContext, GRAPHICS_COLOR_ROYAL_BLUE);


    return(NO_ERR);
}
