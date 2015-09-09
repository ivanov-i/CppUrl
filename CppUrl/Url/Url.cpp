#include "stdafx.h"
#include <string>
#include "Url.h"
#include <regex>
#include <iostream>

Url::Url(std::wstring str)
{
	if(str.empty())
		throw std::invalid_argument("the URL string is empty");
	auto r = std::wregex(L"^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\\?([^#]*))?(#(.*))?");
	auto results = std::wsmatch();
	regex_match(str, results, r);
	Host = results[0];
	Scheme = results[1];
}
