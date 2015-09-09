#include "stdafx.h"
#include <string>
#include "Url.h"
#include <regex>

Url::Url(std::wstring str)
{
	auto r = std::wregex(L"^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\\?([^#]*))?(#(.*))?");
	auto results = std::wsmatch();
	try
	{
		regex_match(str, results, r);
	}
	catch (const std::regex_error& e)
	{
		throw std::invalid_argument(e.what());
	}
	Scheme = results[2].str();
	Authority = results[4].str();
	Path = results[5].str();
	Query = results[7].str();
	Fragment = results[9].str();
}
