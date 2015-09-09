#include "stdafx.h"
#include <string>
#include "Url.h"
#include <regex>
#include <sstream>
#include "Utils.h"

namespace
{
	Url::QueryArgs ParseQueryString(std::string str)
	{
		const auto r = std::regex("([^?=&]+)(=([^&]*))?");
		const auto begin = std::sregex_iterator(std::begin(str), std::end(str), r);
		auto result = Url::QueryArgs();
		for (auto it = begin; it != std::sregex_iterator(); ++it)
		{
			auto name = CommonUtil::UTF8toUCS2((*it)[1].str());
			auto value = CommonUtil::UTF8toUCS2((*it)[3].str());
			result.emplace_back(name, value);
		}
		return result;
	}

	std::string UrlEncode(const std::wstring& str)
	{
		return EncodingUtils::URLEncode(str);
	}

	std::string EncodeExceptQuotes(const std::wstring& str)
	{
		auto isQuoted = str.length() > 2 && str[0] == L'\"' && str[str.length() - 1] == L'\"';
		if(!isQuoted)
		{
			return EncodingUtils::URLEncode(str);
		}
		return "\"" + EncodingUtils::URLEncode(str.substr(1, str.length() - 2)) + '\"';
	}

	std::string CompileQuery(const Url::QueryArgs& queryArgs)
	{
		auto result = std::string();
		for(const auto& arg : queryArgs)
		{
			if (!result.empty())
				result += "&";
			const auto name = EncodeExceptQuotes(arg.first);
			const auto value = EncodeExceptQuotes(arg.second);
			result += name + "=" + value;
		}
		return result;
	}

	void AppendIfNotEmpty(std::ostream& os, const std::string& str, const std::string& prefix, const std::string& postfix)
	{
		if (str.empty())
			return;
		os << prefix << str << postfix;
	}

	void EncodeAndAppendIfNotEmpty(std::ostream& os, const std::wstring& str, const std::string& prefix, const std::string& postfix)
	{
		AppendIfNotEmpty(os, UrlEncode(str), prefix, postfix);
	}
}

void Url::Parse(const std::string& str)
{
	const auto r = std::regex("^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\\?([^#]*))?(#(.*))?");
	auto results = std::smatch();
	std::regex_match(str, results, r);
	Scheme = CommonUtil::UTF8toUCS2(results[2].str());
	Authority = CommonUtil::UTF8toUCS2(results[4].str());
	Path = CommonUtil::UTF8toUCS2(results[5].str());
	Fragment = CommonUtil::UTF8toUCS2(results[9].str());
	Query = ParseQueryString(results[7].str());
}

Url::Url()
{

}

Url::Url(std::string str)
{
	Parse(str);
}

Url::Url(const std::wstring& scheme,
		const std::wstring& authority,
		const std::wstring& path,
		const std::wstring& fragment,
		const std::vector<std::pair<std::wstring, std::wstring>>& query)
	: Scheme{ scheme },
	Authority{ authority },
	Path{ path },
	Fragment{ fragment },
	Query{ query }
{

}

std::string Url::Compile() const
{
	const auto queryStr = CompileQuery(Query);
	std::ostringstream oss;
	EncodeAndAppendIfNotEmpty(oss, Scheme, "", "://");
	EncodeAndAppendIfNotEmpty(oss, Authority, "", "");
	EncodeAndAppendIfNotEmpty(oss, Path, "", "");
	AppendIfNotEmpty(oss, queryStr, "?", "");
	EncodeAndAppendIfNotEmpty(oss, Fragment, "#", "");
	return oss.str();
}
