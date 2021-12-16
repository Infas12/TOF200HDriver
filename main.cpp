#include "serial/serial.h"
#include "math.h"
#include "Time.hpp"
#include "Packet/Packet.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include "Packet/HostPacket.hpp"
#include "crc16.h"
#include "TOF200H.hpp"


#include <unistd.h>


float vx;
float vy;
float vw;

uint8_t buf[5] = {0x01,0x03,0x02,0x00,0x65};

int main(int argc, char** argv)
{
    //std::cout << crc_modbus(buf,5) << std::endl;

    //Initialize Serial
    serial::Serial tof1Serial("/dev/ttyUSB0", 115200, serial::Timeout::simpleTimeout(1000));
    serial::Serial tof2Serial("/dev/ttyUSB1", 115200, serial::Timeout::simpleTimeout(1000));
    TOF200H testTOF1(tof1Serial,0x01);
    TOF200H testTOF2(tof2Serial,0x02);

    // HostPacketManager::Instance()->m_p_serialPort = &testSerial;

    // //Declare Packages.
    // TestPacket testPacket(0x67);
    // testPacket.Registration();

    while (true)
    {
        
        //Restrict rate
        usleep(1000);

        testTOF1.Update();
        testTOF2.Update();

        std::cout << "TOF1:" << testTOF1.m_Distance << "TOF2:" << testTOF2.m_Distance << std::endl;

        //Add logic here

    }


}
