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
				CHECK_THROWS_AS(auto url = Url(emptyString), std::invalid_argument);
			}
		}
		WHEN("the string contains an address")
		{
			auto host = std::wstring(L"127.0.0.1");
			THEN("there is a host")
			{
				CHECK(Url(host).Host == host);
			}
			WHEN("there is a scheme")
			{
				auto scheme = std::wstring(L"http:");
				THEN("the scheme is present")
				{
					auto str = scheme + L"//" + host;
					CHECK(Url(str).Scheme == scheme);
				}
			}
		}
	}
}
