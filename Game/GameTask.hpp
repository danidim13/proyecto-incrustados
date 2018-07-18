/*
 * GameTask.hpp
 *
 *  Created on: Jul 18, 2018
 *      Author: daniel
 */

#ifndef GAME_GAMETASK_HPP_
#define GAME_GAMETASK_HPP_

class GameTask: public Task
{
public:
    GameTask();
    virtual ~GameTask();
    virtual uint8_t run(void);
    virtual uint8_t setup(void);

private:
    GameState m_oGame;
};

#endif /* GAME_GAMETASK_HPP_ */
