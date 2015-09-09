#include "stdafx.h"
#include <string>
#include "Url.h"
#include <regex>

namespace
{
	Url::QueryArgs ParseQueryString(std::wstring str)
	{
		auto r = std::wregex(L"([^?=&]+)(=([^&]*))?");
		auto iterator = std::wsregex_iterator(std::begin(str), std::end(str), r);
		auto result = Url::QueryArgs();
		for (auto it = iterator; it != std::wsregex_iterator(); ++it)
		{
			auto match = *it;
			auto name = match[1].str();
			auto val = match[3].str();
			result.emplace_back(name, val);
		}
		return result;
	}
}
Url::Url(std::wstring str)
{
	auto r = std::wregex(L"^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\\?([^#]*))?(#(.*))?");
	auto results = std::wsmatch();
	regex_match(str, results, r);
	Scheme = results[2].str();
	Authority = results[4].str();
	Path = results[5].str();
	Query = ParseQueryString(results[7].str());
	Fragment = results[9].str();
}
