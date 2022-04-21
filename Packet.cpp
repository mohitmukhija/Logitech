#include "Packet.h"

void Packet::generateSequenceId()
{
    auto softwareId = switchEndian(this->getHeader().softwareId);
    std::string sequenceIdString = switchEndian(std::bitset<16>(HeaderGenerator::getHeaderGenerator().generateSequenceId(softwareId.to_ulong()))).to_string();
    this->getHeader().sequenceIdLSB = std::bitset<8>(sequenceIdString.substr(0, 8));
    this->getHeader().sequenceIdMSB = std::bitset<8>(sequenceIdString.substr(8, 8));
}

Header& Packet::getHeader()
{
    return header;
}

PacketStartDataTransfer::PacketStartDataTransfer()
{
    getHeader().softwareId = HeaderGenerator::getHeaderGenerator().generateSoftwareId();
    generateSequenceId();
    getHeader().packetType = PacketType::StartDataTransfer;
}

std::string PacketStartDataTransfer::generateStream()
{
    return "{";
}

void PacketStartDataTransfer::setPayloadSize(int payloadSize)
{
    this->payloadSize = switchEndian(std::bitset<32>(payloadSize));
}

PacketData::PacketData(const std::bitset<8>& softwareId)
{
    getHeader().softwareId = softwareId;
    generateSequenceId();
    getHeader().packetType = PacketType::Data;
}

std::string PacketData::generateStream()
{
    std::bitset<BitsInChar> currentCharL;
    auto dataSize = switchEndian(payloadSize).to_ulong();

    std::string out;

    out =  "\n\t{";
    for (unsigned long i = 0; i < dataSize * BitsInChar; i++)
    {
        currentCharL[i % BitsInChar] = data[i];
        if (i % BitsInChar == BitsInChar - 1)
        {
            auto currentCharB = switchEndian(currentCharL);
            out += static_cast<char>(currentCharB.to_ulong());
        }
    }
    out += "}";
    return out;
}

bool PacketData::insertData(const char& val)
{
    if (currentIndex + BitsInChar > 472)
        return false;
    auto bitVal = switchEndian(std::bitset<BitsInChar>(val));
    for (int i = 0; i < BitsInChar; i++, currentIndex++)
        data[currentIndex] = bitVal[i];
    this->payloadSize = switchEndian(std::bitset<BitsInChar>(switchEndian(payloadSize).to_ulong() + sizeof(char)));
    return true;
}

PacketStopDataTransfer::PacketStopDataTransfer(const std::bitset<8>& softwareId)
{
    getHeader().softwareId = softwareId;
    generateSequenceId();
    getHeader().packetType = PacketType::StopDataTransfer;
}

std::string PacketStopDataTransfer::generateStream()
{
    return "\n}\n";
}

void PacketStopDataTransfer::setReboot()
{
    reboot.set();
    verify.reset();
    test.reset();
}

void PacketStopDataTransfer::setVerify()
{
    verify.set();
    reboot.reset();
    test.reset();
}

void PacketStopDataTransfer::setTest()
{
    test.set();
    reboot.reset();
    verify.reset();
}
