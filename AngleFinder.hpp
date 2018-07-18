/*
 * AngleFinder.hpp
 *
 *  Created on: May 13, 2018
 *      Author: daniel
 */

#ifndef ANGLEFINDER_HPP_
#define ANGLEFINDER_HPP_

#include "Task.hpp"
#include "arm_math.h"

class AngleFinder: public Task
{
public:
    AngleFinder();
    virtual ~AngleFinder();
    virtual  uint8_t run(void);
    virtual  uint8_t setup(void);
    uint8_t m_u8DrawTask;
private:
    int16_t m_i16LastY;
    float32_t m_fGravityVec[3];

    float32_t m_fForceXY[2];
    float32_t m_fTheta;
    bool m_bFirstTime;

    bool GetGravityVec();
    bool SendHorizon(int16_t i_i16Horizon);
    bool SendForces();
    bool ActivateDisplay();
    float32_t getTheta();
};

#endif /* ANGLEFINDER_HPP_ */
