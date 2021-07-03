#include "serial/serial.h"
#include "math.h"
#include "Tick.h"
#include <iostream>
#include <thread>
#include <chrono>


int main(int argc, char **argv)
{
    //Loop Frequency
    std::chrono::milliseconds period(Tick::getMsPerTick()); //Shouldn't be higher than 100Hz.

    //Initialize Serial
    serial::Serial testSerial("COM4", 115200, serial::Timeout::simpleTimeout(1000));

    while(testSerial.isOpen()){

        //Get Loop start time
        auto start_time = std::chrono::steady_clock::now();

        //Update Tick
        Tick::tick();


        //wait until next loop start.
        std::this_thread::sleep_until(start_time+period);

    }



}

