#include "pch.h"
#include <gtest/gtest.h>
#include "../../Packet.cpp"
#include "../../Util.h"
#include "../../HeaderGenerator.cpp"
#include "../../PacketFactory.cpp"

TEST(PacketFactoryTest, PacketStartDataTransferTest)
{
	auto packetFactory = std::make_unique<PacketFactory>();
	std::bitset<8>softwaerId;
	std::shared_ptr<Packet> packetStartDataTransfer = packetFactory->createPacket(PacketType::StartDataTransfer, softwaerId);
	EXPECT_EQ(packetStartDataTransfer->getHeader().packetType, PacketType::StartDataTransfer);
}

TEST(PacketFactoryTest, PacketDataTest)
{
	auto packetFactory = std::make_unique<PacketFactory>();
	std::bitset<8>softwaerId;
	std::shared_ptr<Packet> packetData = packetFactory->createPacket(PacketType::Data, softwaerId);
	EXPECT_EQ(packetData->getHeader().packetType, PacketType::Data);
}

TEST(PacketFactoryTest, StopDataTransferTest)
{
	auto packetFactory = std::make_unique<PacketFactory>();
	std::bitset<8>softwaerId;
	std::shared_ptr<Packet> packetStopDataTransfer = packetFactory->createPacket(PacketType::StopDataTransfer, softwaerId);
	EXPECT_EQ(packetStopDataTransfer->getHeader().packetType, PacketType::StopDataTransfer);
}

TEST(PacketFactoryTest, PacketDataInsertTest)
{
	auto packetFactory = std::make_unique<PacketFactory>();
	std::bitset<8>softwaerId;
	auto packetData = std::reinterpret_pointer_cast<PacketData>(packetFactory->createPacket(PacketType::Data, softwaerId));
	EXPECT_EQ(packetData->getHeader().packetType, PacketType::Data);
	EXPECT_NO_THROW(packetData->insertData('a'));
	EXPECT_EQ(packetData->generateStream(), "\n\t{a}");
}