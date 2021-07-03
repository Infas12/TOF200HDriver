//
// Created by tiger on 2021/6/27.
//

#include "motor/motor.h"
#include <iostream>

using std::cout;
using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;


motor::motor(int ID,serial::Serial* p_Serial) :
        m_offsetECD(1500), m_p_serialPort(p_Serial), m_waitPeriod(10)
        {
            std::string tmp_ID;
            std::stringstream tmp_ID_buffer;
            tmp_ID_buffer << ID;
            tmp_ID_buffer >> tmp_ID;
            m_IDString = "#"+ tmp_ID +"P"; //convert ID to standard command header.
            motorManager::getInstance()->registerMotor(ID,this);
        }


void motor::update()
{
    ECDtoRadians();
    sendCommand();
}

void motor::ECDtoRadians()
{
    //500-2500 -> -3/4*pi - 3/4*pi

    //Feedback
    int _deltaECD = m_positionFdbECD - m_offsetECD;
    m_positionFdb = static_cast<float>(_deltaECD) / 2000.0 * 3.14159 * 3.0 / 2.0;
    m_positionFdb = m_positionFdb - m_offset;

    //Set
    float _deltaRad = m_positionSet - m_offset;
    auto tmp_ecd = _deltaRad * 2.0 / 3.0 / 3.14159 * 2000.0;
    m_positionSetECD = static_cast<int>(tmp_ecd) + m_offsetECD;

}


void motor::sendCommand()
{

    //just wanna convert int to string...
    std::string tmp_angle;
    std::stringstream tmp_angle_buffer;
    tmp_angle_buffer << m_positionSetECD;
    tmp_angle_buffer >> tmp_angle;

    m_p_serialPort -> write(m_IDString + tmp_angle + "T50\r\n");

}

void motorManager::update()
{
    updateFeedback();
    for(int i = 0;i < 12;i++){
        if(motorList[i]!= nullptr){
            motorList[i]->update();
        }
    }
}


void motorManager::updateFeedback()
{
    std::string* tmp_ID;
    //request feedback
    for(int i = 0;i < 12;i++){
        if(motorList[i]!= nullptr){
            tmp_ID = &(motorList[i]->m_IDString);
            m_p_serialPort -> write(*tmp_ID + "RAD\r\n");
            Sleep(1);//seems like we have to wait between read commands... don't need to do this between set commands.
        }
    }

    int size = m_p_serialPort ->available();
    std::vector<std::string> feedbackMessageList = m_p_serialPort -> readlines(size,"\n");//read all the lines received.

    if(!feedbackMessageList.empty()) {
        for (auto iter = feedbackMessageList.begin(); iter != feedbackMessageList.end(); iter++) {
            try{
                //format: #002P1329
                //ID=002 ECD = 1329
                std::string ID = iter->substr(1,3);
                std::string ECD = iter->substr(5,4);
                int tmp_ID = std::stoi(ID);
                int tmp_ECD = std::stoi(ECD);
                getMotor(tmp_ID)->m_positionFdbECD = tmp_ECD;
            }catch(std::exception e){
                m_p_serialPort->flush(); //reset the serial buffer after fuck up
                std::cerr << *iter << std::endl;
                break;
            }
        }
    }

}









