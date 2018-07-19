#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Entity.hpp"

#define NUM_BOLITAS 3

class GameState {

public:
    GameState();
    virtual ~GameState();

    void GenerateMap();
    void Step();

    void SetGravity(float gx, float gy);


    Entity bolitas[NUM_BOLITAS];


private:

    void GenerateMapRec(bool *map, int8_t x_size, int8_t y_size, int8_t xs, int8_t ys);
    int8_t AdyacentesDisponibles(bool *map, int8_t x_size, int8_t y_size, int8_t xs, int8_t ys);
    int8_t Adyacente(bool *map, int8_t x_size, int8_t y_size, int8_t xs, int8_t ys, int8_t i);

    bool wallmap[(GRID_LX+1)*(GRID_LY+1)];
    float m_drag;

    float m_gx;
    float m_gy;


};
#endif
