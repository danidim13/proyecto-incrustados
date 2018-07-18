/*
 * Compositor.hpp
 *
 *  Created on: Jul 18, 2018
 *      Author: daniel
 */

#ifndef COMPOSITOR_HPP_
#define COMPOSITOR_HPP_

#include "Task.hpp"

extern "C"
{
    #include <driverlib.h>
    #include <grlib.h>
    #include "Crystalfontz128x128_ST7735.h"
}

#include "FramesCommon.hpp"



class Compositor: public Task
{
public:
    Compositor();
    virtual ~Compositor();

    virtual uint8_t run(void);
    virtual uint8_t setup(void);

    uint8_t m_u8RenderTask;

private:

    Graphics_Context m_stContext;

    struct stMapa m_stBackgroud;

    //frame8p_t m_f8pFrame;


    enum State {
        Reset,
        DrawingBg,
        DrawingSpr,
        Finished,
    };
    State m_iState;

    int8_t m_iBgX;
    int8_t m_iBgY;
    int8_t m_iSpr;


    /**
     * Retorna true cuando termina de dibujar el background
     */
    bool DrawBackgroundStep();
    bool DrawElementsStep();
};

#endif /* COMPOSITOR_HPP_ */
