// Logitech.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <bitset>
#include <map>
#include <algorithm>
#include <vector>
#include "PacketFactory.h"


std::vector<std::shared_ptr<Packet>> createPackets(const std::vector<char>& input, char& packetEndFlag)
{
    auto factoryPacket = std::make_unique<PacketFactory>();
    std::vector<std::shared_ptr<Packet>> packetVector;
    std::shared_ptr<PacketData> dataPacket;
    std::bitset<8> bitSoftwareId;

    auto startDataTransferPacket = std::reinterpret_pointer_cast<PacketStartDataTransfer>(factoryPacket->createPacket(PacketType::StartDataTransfer, bitSoftwareId));
    packetVector.push_back(startDataTransferPacket);
    startDataTransferPacket->setPayloadSize(input.size());
    for (auto& currentChar : input)
    {
        if (!dataPacket.get() || !dataPacket->insertData(currentChar))
        {
            dataPacket = std::reinterpret_pointer_cast<PacketData>(factoryPacket->createPacket(PacketType::Data, bitSoftwareId));
            dataPacket->insertData(currentChar);
            packetVector.push_back(dataPacket);
        }
        if (currentChar == packetEndFlag)
        {
            dataPacket = std::reinterpret_pointer_cast<PacketData>(factoryPacket->createPacket(PacketType::Data, bitSoftwareId));
            packetVector.push_back(dataPacket);
        }
    }

    packetVector.push_back(factoryPacket->createPacket(PacketType::StopDataTransfer, bitSoftwareId));

    return packetVector;
}

void printPackets(const std::vector<std::shared_ptr<Packet>>& packetVector)
{
    for (auto& packet : packetVector)
        std::cout << packet->generateStream();
}

int main()
{

    int randSizeOfArrayInput = rand() % 1024;
    std::vector<char> input;
    while (randSizeOfArrayInput > 0)
    {
        input.push_back('!' + rand() % 94);
        randSizeOfArrayInput--;
    }

    char packetEndFlag = '!' + rand() % 94;

    for (auto& x : input)
        std::cout << x;
    std::cout << "\n";
    std::cout << packetEndFlag << "\n";
    packetEndFlag = '+';

    auto packets = createPackets(input, packetEndFlag);
    printPackets(packets);
}
