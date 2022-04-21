#include "PacketFactory.h"

std::shared_ptr<Packet> PacketFactory::createPacket(PacketType packetType, const std::bitset<8>& softwareId)
{
    switch (packetType)
    {
    case PacketType::StartDataTransfer:
        return std::make_shared<PacketStartDataTransfer>();
    case PacketType::StopDataTransfer:
        return std::make_shared<PacketStopDataTransfer>(softwareId);
    default:
        return std::make_shared<PacketData>(softwareId);
    }
}
