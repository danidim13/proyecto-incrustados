#ifndef ENTITY_HPP_
#define ENTITY_HPP_

class Entity {
public:
    Entity() {
        m_x = 128/2;
        m_x = 128/2;
        m_vx = 0;
        m_vy = 0;

    };
    virtual ~Entity(){};

    virtual void Render(){};
    virtual void MoveX(float ax, float drag) {
        m_vx += ax - m_vx*drag;
        m_x += m_vx;
        if (m_x < 0) {
            m_x = 0;
        } else if (m_x > 127) {
            m_x = 127;
        }
    };
    virtual void MoveY(float ay, float drag) {
            m_vy += ay - m_vy*drag;
            m_y += m_vy;
            if (m_y < 0) {
                m_y = 0;
            } else if (m_y > 127) {
                m_y = 127;
            }
        };
private:
    float m_x;
    float m_y;
    float m_vx;
    float m_vy;
};
#endif
