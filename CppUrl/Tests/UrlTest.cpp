#include "stdafx.h"
#include "catch.hpp"
#include <Url.h>

SCENARIO("strings can be parsed", "[Url]")
{
	GIVEN("a string")
	{
		WHEN("the string contains an address")
		{
			THEN("there are fields")
			{
				auto str = std::wstring(L"https://user:pass@host:port/path/subpath?query#fragment");
				auto url = Url(str);
				CHECK(url.Scheme == L"https");
				CHECK(url.Authority == L"user:pass@host:port");
				CHECK(url.Path == L"/path/subpath");
				CHECK(url.Query[0].first == L"query");
				CHECK(url.Fragment == L"fragment");
			}
			WHEN("there is a query")
			{
				auto str = std::wstring(L"https://user:pass@host:port/path/subpath?value1=this&value2=\"that\"&\"value3\"=#fragment");
				THEN("theq query is parsed into arguments")
				{
					auto url = Url(str);
					auto query = url.Query;
					CHECK(query.size() == 3);
				}
			}
		}
	}
}
