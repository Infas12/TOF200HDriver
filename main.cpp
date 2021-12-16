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
    serial::Serial testSerial("/dev/ttyUSB0", 115200, serial::Timeout::simpleTimeout(1000));
    TOF200H testTOF(testSerial,0x01);

    // HostPacketManager::Instance()->m_p_serialPort = &testSerial;

    // //Declare Packages.
    // TestPacket testPacket(0x67);
    // testPacket.Registration();

    while (true)
    {
        
        // Restrict rate
        usleep(1000);

        testTOF.Update();

    }


}
