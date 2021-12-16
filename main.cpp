#include "serial/serial.h"
#include <iostream>
#include <chrono>
#include "TOF200H.hpp"

#include <unistd.h>

int main(int argc, char** argv)
{
    //std::cout << crc_modbus(buf,5) << std::endl;

    //Initialize Serial
    serial::Serial tof1Serial("/dev/ttyUSB0", 115200, serial::Timeout::simpleTimeout(1000));
    serial::Serial tof2Serial("/dev/ttyUSB1", 115200, serial::Timeout::simpleTimeout(1000));
    TOF200H testTOF1(tof1Serial,0x01);
    TOF200H testTOF2(tof2Serial,0x02);


    while (true)
    {
        
        //Restrict rate
        usleep(1000);

        testTOF1.Update();
        testTOF2.Update();

        std::cout << "TOF1:" << testTOF1.m_Distance << "TOF2:" << testTOF2.m_Distance << std::endl;

    }


}
