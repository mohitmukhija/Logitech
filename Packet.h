#pragma once
#include <bitset>
#include "Util.h"
#include "HeaderGenerator.h"
#include <iostream>

enum class PacketType :char
{
    StartDataTransfer = '1',
    Data = '2',
    StopDataTransfer = '3'
};

struct Header
{
    std::bitset<8> softwareId;
    std::bitset<8> sequenceIdLSB;
    std::bitset<8> sequenceIdMSB;
    PacketType packetType;
};


class Packet
{
protected:
    Header header;
public:
    virtual std::string generateStream() = 0;
    void generateSequenceId();
    Header& getHeader();
};

// This class will represent start of data.
class PacketStartDataTransfer : public Packet
{
    std::bitset<32> payloadSize;
public:
    PacketStartDataTransfer();
    virtual std::string generateStream() override;
    void setPayloadSize(int payloadSize);
};

// This class will contain real data
class PacketData : public Packet
{
    int currentIndex = 0;
    std::bitset<8> payloadSize;
    std::bitset<472> data;

public:
    PacketData(const std::bitset<8>& softwareId);
    virtual std::string generateStream() override;
    bool insertData(const char& val);
};

// This class will represent end of data.
class PacketStopDataTransfer : public Packet
{
    std::bitset<1> reboot;
    std::bitset<1> verify;
    std::bitset<1> test;
public:
    PacketStopDataTransfer(const std::bitset<8>& softwareId);
    virtual std::string  generateStream() override;

    // Not using these functions right now. 
    // These should be set as per other rules of the system using these packets.
    void setReboot();
    void setVerify();
    void setTest();
};

