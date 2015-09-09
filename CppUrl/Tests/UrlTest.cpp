#include "stdafx.h"
#include "catch.hpp"
#include <Url.h>

SCENARIO("strings can be parsed", "[Url]")
{
	GIVEN("a string")
	{
		WHEN("the string is empty")
		{
			auto emptyString = std::wstring();
			THEN("throws InvalidArgument exception")
			{
				REQUIRE_THROWS_AS(auto url = Url(emptyString), std::invalid_argument);
			}
		}
		WHEN("the string contains only IP address")
		{
			auto ipAddr = L"127.0.0.1";
			THEN("there is a host")
			{
				auto url = Url(ipAddr);
				REQUIRE(url.Host == ipAddr);
			}
		}
	}
}
