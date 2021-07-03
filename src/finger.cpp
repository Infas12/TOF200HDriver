//
// Created by tiger on 2021/7/2.
//

#include <iostream>
#include "finger.h"



finger::finger(int leftMotorID, int rightMotorID, serial::Serial *serial) :
        m_leftMotor(leftMotorID,serial),m_rightMotor(rightMotorID,serial)
        {
            m_xPos = 0.0;
            m_yPos = 100.0;
        }

void finger::update()
{
    updateIK();
    m_leftMotor.setPosition(m_leftAngleSet);
    m_rightMotor.setPosition(m_rightAngleSet);
}

void finger::updateIK()
{
    m_leftAngleSet = singleIK(LO/2.0+m_xPos,m_yPos) - 3.14159/2.0;
    m_rightAngleSet = -singleIK(LO/2.0-m_xPos,m_yPos) + 3.14159/2.0;
}

float finger::singleIK(float x, float y)
{
    auto A = ((x*x) + (y*y) - (L1*L1) - (L2*L2))/(2*L1*L2);
    auto q2 = 2.0*3.14159 - acos(A);
    auto q4 = atan2(L2*sin(q2),(L2*cos(q2)+L1));
    auto q3 = atan2(y,x);
    auto q1 = q3-q4;

    return static_cast<float>(q1);
}