#include "TOF200H.hpp"
#include "crc16.h"
#include <iostream>

TOF200H::TOF200H(serial::Serial& serial,uint8_t id) :   m_serial(serial),
                                                        m_Buffer{0},
                                                        m_BufferFront(0),
                                                        m_BufferRear(0),
                                                        m_CheckingHead(0),
                                                        m_DeviceID(id),
                                                        m_ReceivedHeader(false),
                                                        m_PacketBuffer{0}
                                        
{
}

void TOF200H::Enqueue(uint8_t* pData, uint32_t len)
{
    for(int i = 0; i < len; i++)
    {
        m_Buffer[m_BufferRear] = pData[i];
        m_BufferRear = (m_BufferRear + 1) % BUFFER_LEN;
    }
}

static uint8_t buffer[64];
void TOF200H::Update()
{
    //TODO: fix this
    int len = m_serial.available();
    m_serial.read(buffer,len);
    Enqueue(buffer,len);

    //unpack
    while(m_CheckingHead != m_BufferRear)
    {
        uint8_t data = m_Buffer[m_CheckingHead];
        
        if(m_ReceivedHeader)
        {
            m_PacketBuffer[m_PacketReceivedLen] = data;
            m_PacketReceivedLen++;

            if(m_PacketReceivedLen == 3)
            {
                m_ExpectedLen = m_PacketBuffer[2] + 5; //1ID + 1Fcn + 1Len + 2CrC16 = 5bytes
                if(m_ExpectedLen > 20 ){
                    m_CheckingHead = (m_CheckingHead + BUFFER_LEN - 2) % BUFFER_LEN;
                    m_ReceivedHeader = false;
                }
            }
            
            if(m_PacketReceivedLen==m_ExpectedLen)
            {
                uint16_t CheckSum = crc_modbus(m_PacketBuffer,m_ExpectedLen-2);
                uint16_t ReceivedCheckSum = m_PacketBuffer[m_ExpectedLen-1] << 8 | m_PacketBuffer[m_ExpectedLen-2];
                if(CheckSum==ReceivedCheckSum)
                {
                    m_BufferFront = m_CheckingHead;
                    HandlePacket();
                    m_ReceivedHeader = false;

                }
                else
                {
                    m_CheckingHead = (m_CheckingHead + BUFFER_LEN - m_ExpectedLen + 1) % BUFFER_LEN;
                    m_ReceivedHeader = false;
                }
            }

        }

        if(!m_ReceivedHeader)
        {
            if(data==m_DeviceID)
            {   
                m_ReceivedHeader  = true;
                m_PacketReceivedLen = 0;
                m_PacketBuffer[m_PacketReceivedLen] = data;
                m_PacketReceivedLen ++;
            }
        }

        m_CheckingHead = (m_CheckingHead + 1) % BUFFER_LEN;

    }
}

void TOF200H::HandlePacket()
{
    uint8_t FunctionType = m_PacketBuffer[1];
    switch(FunctionType)
    {
        case 0x03:
            m_Distance = m_PacketBuffer[3] << 8 | m_PacketBuffer[4];
            std::cout << m_Distance << std::endl;
            break;
        default:
            std::cout << "Handler Not Implemented." << std::endl;
            break;
    }

}