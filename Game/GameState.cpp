
#include "GameState.hpp"

GameState::GameState()
{
    m_gx = 0;
    m_gy = 0;
    m_drag = 0.3;
}
GameState::~GameState()
{

}

void GameState::Step()
{

    bolita.MoveX(m_gx, m_drag);
    bolita.MoveY(m_gy, m_drag);
    // TODO
}

void GameState::GenerateMap()
{
    // TODO
}

void GameState::SetGravity(float gx, float gy)
{
    m_gx = gx;
    m_gy = gy;
}
