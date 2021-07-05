#ifndef HOSTPACKET_HPP
#define HOSTPACKET_HPP

#include "Packet.hpp"
#include "serial/serial.h"


class HostPacketManager : public PacketManager
{
private:
    StreamChannel m_StreamChannel;

public:
    HostPacketManager();

    serial::Serial* m_p_serialPort; //must be set before Packet registration.

    virtual void Init();
    virtual void Update();
    static HostPacketManager* Instance()
    {
        static HostPacketManager instance;
        return &instance;
    }
};

class HostPacket : public Packet
{
private:
    serial::Serial* m_p_serialPort;

public:
    HostPacket(uint8_t _id):Packet(_id){}

    virtual void Registration()
    {
        HostPacketManager::Instance()->PacketHandlerRegistration(0, m_ProtocolId, this);
        m_p_serialPort = HostPacketManager::Instance() -> m_p_serialPort;
    }

    virtual void SendPacket();

};

class EulerPacket : public HostPacket
{
private:
    float m_Yaw;
    float m_Pitch;
    float m_Roll;
public:
    EulerPacket(uint8_t _id) : HostPacket(_id){}
    void Send(float _yaw, float _pitch, float _roll);
    virtual void OnPacketReceived();
    template<typename Stream> void SerializePacket(Stream &stream);

    float GetYaw(){ return m_Yaw; }
    float GetPitch(){ return m_Pitch; }
    float GetRoll(){ return m_Roll; }
};

#endif
