#pragma once
#include <string>

namespace CommonUtil
{
	std::wstring UTF8toUCS2(const std::string & src);
	std::string UCS2toUTF8(const std::wstring & src);
}
namespace EncodingUtils
{
	std::string URLEncode(const std::wstring & strIn);
	std::string URLEncode(const std::string & strUTF8In);
}
