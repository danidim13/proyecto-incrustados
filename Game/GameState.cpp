
#include "GameState.hpp"
#include "stdlib.h"

GameState::GameState()
{
    m_gx = 0;
    m_gy = 0;
    m_drag = 0.1;
}
GameState::~GameState()
{

}

void GameState::Step()
{
    for (int i = 0; i < NUM_BOLITAS; i++) {
        bolitas[i].StainBackground();
        bolitas[i].MoveX(m_gx, m_drag);
        bolitas[i].MoveY(m_gy, m_drag);
    }

    //bolita.StainBackground();
    // TODO
}

void GameState::GenerateMap()
{
    int8_t x_size = GRID_LX+1;
    int8_t y_size = GRID_LY+1;

    // True es que hay pared
    //bool wallmap[x_size*y_size];
    for (int j = 0; j < y_size; j++) {
        for (int i = 0; i < x_size; i++) {
            if (i == 0 || i == x_size -1 ||
                    j == 0 || j == y_size -1) {
                wallmap[j*x_size + i] = true;
            } else {
                wallmap[j*x_size + i] = false;
            }
        }
    }

    int xs;
    int ys;

    // Se selecciona el punto de partida
    // no puede ser una esquina.
    int lado = rand()%4;

    // TOP 0
    if (lado == 0) {
        xs = (rand() % x_size -2) + 1;
        ys = 0;
    // LEFT 1
    } else if (lado == 1) {
        xs = 0;
        ys = (rand() % y_size -2) + 1;
    // BOT 2
    } else if (lado == 2) {
        xs = (rand() % x_size -2) + 1;
        ys = y_size -1;
    // RIGHT 3
    } else {
        xs = x_size -1;
        ys = (rand() % y_size -2) + 1;

    }




    GenerateMapRec(wallmap, x_size, y_size, xs, ys);
    // TODO
}

void GameState::GenerateMapRec(bool *map, int8_t x_size, int8_t y_size, int8_t xs, int8_t ys) {
    //int xnext, ynext;

    int8_t opciones = AdyacentesDisponibles(map, x_size, y_size, xs, ys);

    while(opciones > 0) {
        int8_t o = rand() % opciones;

        int8_t lado = Adyacente(map, x_size, y_size, xs, ys, o);

        switch(lado){
        // TOP
        case 0: {
            break;
        }
        // Left
        case 1: {
            map[ys*x_size + xs - 1] = true;
            g_stBackground.grid[(ys-1)*GRID_LX + xs-1] |= BOT_B ;
            g_stBackground.grid[(ys)*GRID_LX + xs-1] |= TOP_B ;
            GenerateMapRec(map, x_size, y_size, xs - 1, ys);
            break;
        }
        // BOT
        case 2: {
            map[(ys+1)*x_size + xs] = true;
            g_stBackground.grid[(ys)*GRID_LX + xs] |= RIGHT_B ;
            g_stBackground.grid[(ys)*GRID_LX + xs+1] |= LEFT_B ;
            GenerateMapRec(map, x_size, y_size, xs + 1, ys);
            break;
        }
        // RIGHT
        case 3: {
            map[ys*x_size + xs + 1] = true;
            g_stBackground.grid[(ys-1)*GRID_LX + xs] |= BOT_B ;
            g_stBackground.grid[(ys)*GRID_LX + xs] |= TOP_B ;
            GenerateMapRec(map, x_size, y_size, xs + 1, ys);
            break;
        }
        default:
            while(true);
        }
        opciones = AdyacentesDisponibles(map, x_size, y_size, xs, ys);
    }

    return;
}

int8_t GameState::AdyacentesDisponibles(bool *map, int8_t x_size, int8_t y_size, int8_t xs, int8_t ys) {
    int8_t count = 0;

    // TOP
    if (ys > 0 && map[(ys-1)*x_size + xs])
        count++;
    // Left
    if (xs > 0 && map[ys*x_size + xs - 1])
        count++;
    // Bot
    if (ys + 1 < y_size && map[(ys+1)*x_size + xs])
        count++;
    // Right
    if (xs + 1 < x_size && map[ys*x_size + xs + 1])
        count++;



    return count;
}

int8_t GameState::Adyacente(bool *map, int8_t x_size, int8_t y_size, int8_t xs, int8_t ys, int8_t i) {
    int count = 0;

    // TOP
    if (ys > 0 && map[(ys-1)*x_size + xs]) {
        if (i == count)
            return 0;
        count++;
    }
    // Left
    if (xs > 0 && map[ys*x_size + xs - 1]) {
        if (i == count)
            return 1;
        count++;
    }

    // Bot
    if (ys + 1 < y_size && map[(ys+1)*x_size + xs]) {
        if (i == count)
            return 2;
        count++;
    }
    // Right
    if (xs + 1 < x_size && map[ys*x_size + xs + 1]) {
        if (i == count)
            return 3;
        count++;
    }
    return -1;

}

void GameState::SetGravity(float gx, float gy)
{
    m_gx = gx;
    m_gy = gy;
}
