#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Entity.hpp"

class GameState {

public:
    GameState();
    virtual ~GameState();

    void GenerateMap();
    void Step();

    void SetGravity(float gx, float gy);


private:
    Entity bolita;

    float m_drag;

    float m_gx;
    float m_gy;


};
#endif
