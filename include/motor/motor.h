//
// Created by tiger on 2021/6/27.
//

#ifndef SERIAL_MOTOR_H
#define SERIAL_MOTOR_H


#include <string>
#include <chrono>
#include <thread>
#include "serial/serial.h"
#include <windows.h>
#include <map>

class motorManager; //forward declaration

class motor {
private:

    int m_ID;
    std::string m_IDString; //bus ID

    float m_offset = 0; //offset angle(radians); aka the original position
    float m_positionSet;
    float m_positionFdb; //feedback angle in radians;

    int m_offsetECD = 1500;
    int m_positionSetECD;
    int m_positionFdbECD;

    serial::Serial* m_p_serialPort;

    std::chrono::milliseconds m_waitPeriod;

public:

    friend class motorManager;

    motor(int ID,serial::Serial* p_Serial);
    void update();
    void ECDtoRadians();
    void sendCommand();
    void setPosition(float pos){m_positionSet = pos;}
    float getPositionFdb(){return m_positionFdb;}


};

class motorManager{
private:
    motorManager(){};
    motor* motorList[12] {nullptr};
    serial::Serial* m_p_serialPort;


public:

    static motorManager* getInstance(){
        static motorManager instance;
        return &instance;
    }

    void setSerialPort(serial::Serial* p_serial){m_p_serialPort = p_serial;}

    void registerMotor(int ID,motor* p_motor){
        motorList[ID] = p_motor;
    }

    motor* getMotor(int ID){
        return motorList[ID];
    }

    void update();

    void updateFeedback();

};

#endif //SERIAL_MOTOR_H
