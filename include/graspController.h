//
// Created by tiger on 2021/7/2.
//

#ifndef SERIAL_GRASPCONTROLLER_H
#define SERIAL_GRASPCONTROLLER_H
#include "serial/serial.h"
#include "HandConfig.h"

enum graspState{
    OFF = 0,
    SPINNING,
    ALL,
};

class graspController{

private:
    serial::Serial* m_p_serialPort;
    graspState m_state = OFF;
    graspController(){};
    float baseAngleFeedback[3];//TODO: use the count of fingers after "hand" class added

public:
    void update();
    void updateFeedback();
    static graspController* getInstance(){
        static graspController instance;
        return &instance;
    }
    void setSerialPort(serial::Serial* p_serial){
        m_p_serialPort = p_serial;
    }
    void sendCommand();
    float getBaseFeedback(int index){return baseAngleFeedback[index];} //TODO: use the

};

#endif //SERIAL_GRASPCONTROLLER_H
