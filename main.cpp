#include "serial/serial.h"
#include "motor/motor.h"
#include "finger.h"
#include "math.h"
#include "Tick.h"
#include "graspController.h"
#include <iostream>
#include <thread>
#include <chrono>


int main(int argc, char **argv)
{
    //Loop Frequency
    std::chrono::milliseconds period(Tick::getMsPerTick()); //Shouldn't be higher than 100Hz.

    //Initialize Serial
    serial::Serial motorSerial("COM4", 115200, serial::Timeout::simpleTimeout(1000));
    //serial::Serial arduinoSerial("COM5",115200,serial::Timeout::simpleTimeout(1000));

    //Initialize Finger
    finger testFinger = finger(1,2,&motorSerial);

    //Initialize Grasp
    //graspController::getInstance()->setSerialPort(&arduinoSerial);

    //Initialize MotorManager
    motorManager::getInstance()->setSerialPort(&motorSerial);

    while(motorSerial.isOpen()){

        //Get Loop start time
        auto start_time = std::chrono::steady_clock::now();

        //Update Tick
        Tick::tick();

        //test stuff, draw a circle.
        auto xPos = 40.0 * sin((float)Tick::getTick()*0.1);
        auto yPos = 100.0 + 40.0 * cos((float)Tick::getTick()*0.1);

        //Update Finger Position
        testFinger.setX(xPos);
        testFinger.setY(yPos);
        testFinger.update();

        //Update Motor Control.
        motorManager::getInstance()->update();

        //Update Grasper Control
        //graspController::getInstance()->update();

        //TODO: synchronize feedbacks.

        //wait until next loop start.
        std::this_thread::sleep_until(start_time+period);



    }



}

