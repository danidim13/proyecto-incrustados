#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "msp.h"
#include "arm_math.h"
#include "FramesCommon.hpp"

#include "stdlib.h"

class Entity {
public:
    Entity() {

        m_x = CELL_X/2.0;
        m_y = CELL_Y/2.0;

        m_vx = 0;
        m_vy = 0;
        m_radius = 4;

    };
    virtual ~Entity(){};

    virtual void Spawn() {
        int r = (rand() % GRID_LX) * CELL_X;

        m_x = (float)r + CELL_X/2.0;

        r = (rand() % GRID_LY) * CELL_Y;
        m_y = (float)r + CELL_Y/2.0;
    }
    virtual void Render(){};
    virtual void MoveX(float ax, float drag) {
        float diff;
        m_vx += ax - m_vx*drag;
        m_x += m_vx;
        if (m_x < m_radius) {
            diff = m_radius - m_x;
            m_x = m_radius + diff;
            m_vx = -m_vx;
        } else if (m_x > 127 - m_radius) {
            diff = m_x - (127 - m_radius);
            m_x = 127 - m_radius;
            m_vx = -m_vx;
        }
    };
    virtual void MoveY(float ay, float drag) {
        float diff;
            m_vy += ay - m_vy*drag;
            m_y += m_vy;
            if (m_y < m_radius) {
                diff = m_radius - m_y;
                m_y = m_radius + diff;
                m_vy = -m_vy;
            } else if (m_y > 127 - m_radius) {
                diff = m_y - (127 - m_radius);
                m_y = 127 - m_radius;
                m_vy = -m_vy;
            }
        };
    virtual void GetPos(int32_t * x, int32_t * y, int32_t * r) {
        *x = m_x;
        *y = m_y;
        *r = m_radius;
    }
    virtual void StainBackground() {
        int x1 = (int)m_x - m_radius;
        int x2 = x1 + 2*m_radius;
        int y1 = (int)m_y - m_radius;
        int y2 = y1 + 2*m_radius;

        x1 = x1 / CELL_X;
        x2 = x2 / CELL_X;
        y1 = y1 / CELL_Y;
        y2 = y2 / CELL_Y;
        g_stBackground.grid[y1 * GRID_LX +  x1] |= DIRTY_B;
        g_stBackground.grid[y2 * GRID_LX +  x1] |= DIRTY_B;
        g_stBackground.grid[y1 * GRID_LX +  x2] |= DIRTY_B;
        g_stBackground.grid[y2 * GRID_LX +  x2] |= DIRTY_B;
    }
private:
    int m_radius;
    float m_x;
    float m_y;
    float m_vx;
    float m_vy;
};
#endif
