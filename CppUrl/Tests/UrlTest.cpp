#include "stdafx.h"
#include "catch.hpp"
#include <Url.h>

SCENARIO("strings can be parsed", "[Url]")
{
	GIVEN("a string")
	{
		WHEN("the string contains an address")
		{
			auto host = std::wstring(L"https://user:pass@host:port/path/subpath?query#fragment");
			THEN("there are fields")
			{
				auto url = Url(host);
				CHECK(url.Scheme == L"https");
				CHECK(url.Authority == L"user:pass@host:port");
				CHECK(url.Path == L"/path/subpath");
				CHECK(url.Query == L"query");
				CHECK(url.Fragment == L"fragment");
			}
//			When
			//queryVal1=10&val2=23
		}
	}
}
