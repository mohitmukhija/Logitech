#include "pch.h"
#include "../../Util.h"
#include <bitset>

TEST(SwitchEndian, SwicthCheck)
{
	std::bitset<4> bitVal(1);
	if (bitVal[0] == 0)
	{
		EXPECT_EQ(bitVal[0], 0);
		bitVal = switchEndian(bitVal);
		EXPECT_EQ(bitVal[0], 0);
	}
	else
	{
		EXPECT_EQ(bitVal[0], 1);
		bitVal = switchEndian(bitVal);
		EXPECT_EQ(bitVal[0], 0);
	}
}
