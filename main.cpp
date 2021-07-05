#include "serial/serial.h"
#include "math.h"
#include "Time.hpp"
#include "Packet/Packet.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include "Packet/HostPacket.hpp"

int main(int argc, char **argv)
{
    //Loop Frequency
    std::chrono::milliseconds period(Time::getMsPerTick()); //Shouldn't be higher than 100Hz.

    //Initialize Serial
    serial::Serial testSerial("COM1", 115200, serial::Timeout::simpleTimeout(1000));
    HostPacketManager::Instance()->m_p_serialPort = &testSerial;

    EulerPacket eulerPacket(0x5A);
    eulerPacket.Registration();

    while(testSerial.isOpen()){

        //Get Loop start time
        auto start_time = std::chrono::steady_clock::now();

        //Update Time
        Time::tick();

        //test stuff.
        eulerPacket.Send(sin(Time::getTick()*0.01),cos(Time::getTick()*0.01),3);

        //update Packets.
        HostPacketManager::Instance()->Update();

        //wait until next loop start.
        std::this_thread::sleep_until(start_time+period);

    }



}

