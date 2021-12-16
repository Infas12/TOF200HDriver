#ifndef TOF200H_HPP
#define TOF200H_HPP

#include "serial/serial.h"
#define BUFFER_LEN 256


class TOF200H
{
private:

    uint8_t m_DeviceID;

    serial::Serial& m_serial;
    uint8_t m_Buffer[BUFFER_LEN];
    uint8_t m_BufferFront;
    uint8_t m_BufferRear;
    uint8_t m_CheckingHead;
    
    bool    m_ReceivedHeader;
    uint8_t m_PacketBuffer[16];
    uint8_t m_PacketReceivedLen;
    uint8_t m_ExpectedLen;

public:

    uint16_t m_Distance;

    TOF200H(serial::Serial& serial,uint8_t id);
    void Enqueue(uint8_t* pData, uint32_t len);
    void Update();
    void HandlePacket();

};


#endif