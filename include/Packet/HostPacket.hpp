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

class EncoderPacket : public HostPacket
{
private:
    float m_Encoder0;
    float m_Encoder1;
    float m_Encoder2;
    float m_Encoder3;
public:
    EncoderPacket(uint8_t _id) : HostPacket(_id){}
    void Send(float _ECD0, float _ECD1, float _ECD2,float _ECD3);
    virtual void OnPacketReceived();
    template<typename Stream> void SerializePacket(Stream &stream);

};

class MotorSetPacket : public HostPacket
{
public:
    float m_posSet0;
    float m_posSet1;
    float m_posSet2;
    float m_posSet3;
public:
    MotorSetPacket(uint8_t _id) : HostPacket(_id){}
    void Send(float _set0, float _set1, float _set2, float _set3);
    virtual void OnPacketReceived();
    template<typename Stream> void SerializePacket(Stream &stream);
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

    static EulerPacket* Instance()
    {
        static EulerPacket instance(0x5A);
        return &instance;
    }
    
    float GetYaw(){ return m_Yaw; }
    float GetPitch(){ return m_Pitch; }
    float GetRoll(){ return m_Roll; }
};

class TestPacket : public HostPacket
{
public:
    TestPacket(uint8_t _id):HostPacket(_id){}
    float m_Vx;
    float m_Vy;
    float m_Vw;
    virtual void OnPacketReceived();
    virtual void SendPacket();
    template<typename Stream> void SerializePacket(Stream &stream);
};



#endif
