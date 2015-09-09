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
				auto str = std::string("https://user:pass@host:port/path/subpath?query#fragment");
				auto url = Url(str);
				CHECK(url.Scheme == L"https");
				CHECK(url.Authority == L"user:pass@host:port");
				CHECK(url.Path == L"/path/subpath");
				CHECK(url.Query[0].first == L"query");
				CHECK(url.Fragment == L"fragment");
			}
			AND_WHEN("there is a query")
			{
				auto str = std::string("https://user:pass@host:port/path/subpath?value1=this&value2=\"that\"&\"value3\"=#fragment");
				THEN("the query is parsed into arguments")
				{
					auto url = Url(str);
					auto query = url.Query;
					CHECK(query.size() == 3);
				}
			}
		}
	}
}
	
SCENARIO("URL can be compiled", "[Url]")
{
	GIVEN("an Url object")
	{
		WHEN("fields are empty")
		{
			THEN("it builds an empty URL")
			{
				CHECK(Url().Compile() == "");
			}
		}
		WHEN("all fields are non-empty")
		{
			AND_WHEN("are all ASCII")
			{
				auto args = Url::QueryArgs();
				args.emplace_back(L"name", L"value");
				args.emplace_back(L"name1", L"value1");
				args.emplace_back(L"name2", L"");
				args.emplace_back(L"", L"value3");
				auto url = Url(L"http", L"localhost", L"/path/subpath", L"fragment", args);

				THEN("the result is not encoded")
				{
					CHECK(url.Compile() == "http://localhost/path/subpath?name=value&name1=value1&name2=&=value3#fragment");
				}
			}
			AND_WHEN("all fields are non-ASCII")
			{
				auto args = Url::QueryArgs();
				args.emplace_back(L"\"na me", L"va\"lu e");

				auto url = Url(L"http", L"localhost", L"/pa th/sub\"path", L"frag me\"nt", args);

				THEN("the result is encoded")
				{
					CHECK(url.Compile() == "http://localhost/pa%20th/sub%22path?%22na%20me=va%22lu%20e#frag%20me%22nt");
				}
			}
		}
		WHEN("query arguments are quoted")
		{
			auto args = Url::QueryArgs();
			args.emplace_back(L"\"na me\"", L"\"va\"lu e\"");

			THEN("quotes are not encoded")
			{
				auto url = Url(L"", L"", L"", L"", args);
				CHECK(url.Compile() == "?\"na%20me\"=\"va%22lu%20e\"");
			}
		}
	}
}