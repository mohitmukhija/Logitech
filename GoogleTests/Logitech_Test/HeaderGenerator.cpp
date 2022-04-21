#include "pch.h"
#include <gtest/gtest.h>
#include "../../Util.h"
#include "../../HeaderGenerator.h"

TEST(HeaderGeneratorTest, GenerateSoftwareIdTest)
{
	auto softwareId = HeaderGenerator::getHeaderGenerator().generateSoftwareId();
	EXPECT_EQ(softwareId, 1);
	softwareId = HeaderGenerator::getHeaderGenerator().generateSoftwareId();
	EXPECT_EQ(softwareId, 2);
}
TEST(HeaderGeneratorTest, GenerateSequenceIdTest)
{
	auto softwareId = HeaderGenerator::getHeaderGenerator().generateSoftwareId();
	EXPECT_EQ(softwareId, 3);

	auto sequenceId = HeaderGenerator::getHeaderGenerator().generateSequenceId(softwareId);
	EXPECT_EQ(sequenceId, 1);

	sequenceId = HeaderGenerator::getHeaderGenerator().generateSequenceId(softwareId);
	EXPECT_EQ(sequenceId, 2);

	softwareId = HeaderGenerator::getHeaderGenerator().generateSoftwareId();
	EXPECT_EQ(softwareId, 4);

	sequenceId = HeaderGenerator::getHeaderGenerator().generateSequenceId(softwareId);
	EXPECT_EQ(sequenceId, 1);

	sequenceId = HeaderGenerator::getHeaderGenerator().generateSequenceId(softwareId);
	EXPECT_EQ(sequenceId, 2);
}