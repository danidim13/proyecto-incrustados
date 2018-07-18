/*
 * GameTask.hpp
 *
 *  Created on: Jul 18, 2018
 *      Author: daniel
 */

#ifndef GAME_GAMETASK_HPP_
#define GAME_GAMETASK_HPP_

#include "Task.hpp"


#include "GameState.hpp"
#include "msp.h"
#include "arm_math.h"

class GameTask: public Task
{
public:
    GameTask();
    virtual ~GameTask();
    virtual uint8_t run(void);
    virtual uint8_t setup(void);
    Entity* GetEntities(int * i_iElem);

private:
    GameState m_oGame;

    float32_t m_fForceScale;
    float32_t m_fXforce;
    float32_t m_fYforce;

    bool GetXYForce();
};

#endif /* GAME_GAMETASK_HPP_ */
