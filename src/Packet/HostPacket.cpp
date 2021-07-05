#include "Packet/HostPacket.hpp"

HostPacketManager::HostPacketManager() : PacketManager(1)
{
    m_pChannel = &m_StreamChannel;
}

void HostPacketManager::Init()
{
    PacketManager::Init();
}

void HostPacket::SendPacket()
{
    if(!m_p_serialPort->isOpen()||m_p_serialPort== nullptr)
    {
        return;
    }

    m_p_serialPort->write(m_Buffer, m_DataLen + 8);
}

void EulerPacket::Send(float _yaw, float _pitch, float _roll)
{
    m_Yaw = _yaw;
    m_Pitch = _pitch;
    m_Roll = _roll;

    SerializePacket(m_OutputStream);
    HostPacket::SendPacket();
}

void EulerPacket::OnPacketReceived()
{
    SerializePacket(m_InputStream);
}

template<typename Stream>
void EulerPacket::SerializePacket(Stream &stream)
{
    m_DataLen = 6;

    SerializeHeader(stream);

    stream.SerializeFloat(m_Yaw, - 3.14159, 0.0001f);
    stream.SerializeFloat(m_Pitch, - 3.14159, 0.0001f);
    stream.SerializeFloat(m_Roll, - 3.14159, 0.0001f);

    SerializeCrc16(stream);
}




static uint8_t buffer[64];
void HostPacketManager::Update()
{
    if(m_p_serialPort== nullptr){
        return;
    }

    //collect data from serial port.
    uint8_t length = m_p_serialPort->available();
    m_p_serialPort->read(buffer,length);
    Enqueue(0,buffer,length);
    PacketManager::Update();
}