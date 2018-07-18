/*
 * FrameBuffer.hpp
 *
 *  Created on: Jul 17, 2018
 *      Author: daniel
 */

#ifndef FRAMEBUFFER_HPP_
#define FRAMEBUFFER_HPP_

#include "Task.hpp"

extern "C"
{
    #include <driverlib.h>
    #include <grlib.h>
    #include "Crystalfontz128x128_ST7735.h"
}

#include "FramesCommon.hpp"

class FrameBuffer: public Task
{
public:
    FrameBuffer();
    virtual ~FrameBuffer();

    virtual uint8_t run(void);
    virtual uint8_t setup(void);

    uint8_t m_u8CompositorTask;

private:

    Graphics_Context m_stContext;

    bool m_bNextFrameReady;
    int16_t m_u16Row;

    enum State {
        Reset,
        Drawing,
        NotifyCompositor,
    };

    State m_iState;

    frame8_t m_f8Frame0;
    frame8_t m_f8Frame1;

    frame8p_t m_f8pFgFrame;
    frame8p_t m_f8pBgFrame;

    void ReadMsgs();
    bool DrawFrame();
    void DrawRow();
    void SwitchFrame();
    bool SendBGFrame();

    void ClearFrame(frame8p_t f);

};

#endif /* FRAMEBUFFER_HPP_ */
