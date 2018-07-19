/*
 * Compositor.hpp
 *
 *  Created on: Jul 18, 2018
 *      Author: daniel
 */

#ifndef COMPOSITOR_HPP_
#define COMPOSITOR_HPP_

#include "Task.hpp"
#include "Entity.hpp"

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

    void SetEntities(Entity* entities, int numEntities);

    uint8_t m_u8RenderTask;

private:

    Graphics_Context m_stContext;

    //struct stMapa m_stBackgroud;

    Entity* m_pEntities;
    int m_iNumEntities;

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
    int8_t m_iWcnt;

    int m_iWaitCicles;


    /**
     * Retorna true cuando termina de dibujar el background
     */
    bool DrawBackgroundStep();

    /**
     * Retorna true cuando termina de dibujar los objetos
     */
    bool DrawElementsStep();

    /**
     * Marca todos los bits de dirty en el background.
     */
    void ResetBackground();
};

#endif /* COMPOSITOR_HPP_ */
