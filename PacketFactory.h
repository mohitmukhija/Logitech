#pragma once
#include "Packet.h"

// factory class to generate header based on packet type.
class PacketFactory
{
public:
    std::shared_ptr<Packet> createPacket(PacketType packetType, const std::bitset<8>& softwareId);
};
