/*
 * Display.hpp
 *
 *  Created on: May 13, 2018
 *      Author: joror
 */

#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

//#define __NOP __nop
#include "msp.h"
#include "Task.hpp"

extern "C"
{
    #include <driverlib.h>
    #include <grlib.h>
    #include "Crystalfontz128x128_ST7735.h"
}

#define DD_DOWN 0
#define DD_UP   1

#define SMALL_LINE 25
#define SMALL_LINE_WIDTH 25

#define LONG_LINE 50
#define LONG_LINE_WIDTH 75

class Display : public Task
{
    public:
        Display();
        //uint16_t m_u16BITN;
        virtual uint8_t run(void);
        virtual uint8_t setup(void);

    protected:
    private:
        Graphics_Context m_stContext;
        int16_t m_i16HorizonHeight;
        int16_t m_i16NextHorizon;
        int8_t m_i8DrawDir;
        bool GetHorizon();

        uint16_t m_u16DrawIter;
        void DrawSectionDown();
        void DrawSectionUp();

        void DrawHalfLine(int16_t i_i16Width, int16_t i_i16Y, int32_t i_i32Color);
};

#endif /* DISPLAY_HPP_ */
