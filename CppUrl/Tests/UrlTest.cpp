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
	}
}