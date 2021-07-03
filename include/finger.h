//
// Created by tiger on 2021/7/2.
//

#ifndef SERIAL_FINGER_H
#define SERIAL_FINGER_H

#include "motor/motor.h"
#include <queue>
#include "math.h"
#include "serial/serial.h"
#include "HandConfig.h"

class finger {

private:
    motor m_leftMotor;
    motor m_rightMotor;
    float m_leftAngleSet;
    float m_rightAngleSet;
    float m_xPos;
    float m_yPos;
    std::queue<float[2]> m_traj;

public:


    finger(int leftMotorID,int rightMotorID,serial::Serial* serial);

    void update();
    void updateIK();
    float singleIK(float x,float y);
    void reset(){m_xPos = 0.0f;m_yPos = 100.0f;};
    void setX(float x){m_xPos = x;}
    void setY(float y){m_yPos = y;}

};


#endif //SERIAL_FINGER_H
