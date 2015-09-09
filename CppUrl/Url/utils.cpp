#include "stdafx.h"
#include <string>
#include <windows.h>
#include "Utils.h"


namespace CommonUtil
{
	const WCHAR INVALID_WCHAR = L'_';
	const CHAR	INVALID_CHAR = '_';

	std::wstring UTF8toUCS2(const std::string & src)
	{
		if (src.empty())
			return L"";
		int nRequiredSize = MultiByteToWideChar(CP_UTF8, 0, src.c_str(), -1, NULL, 0);
		std::wstring result(nRequiredSize - 1, INVALID_WCHAR);
		MultiByteToWideChar(CP_UTF8, 0, src.c_str(), -1, &result[0], nRequiredSize);
		return result;
	}

	std::string UCS2toUTF8(const std::wstring & src)
	{
		if (src.empty())
			return "";
		int nRequiredSize = WideCharToMultiByte(CP_UTF8, 0, src.c_str(), -1, NULL, 0, NULL, NULL);
		std::string result(nRequiredSize - 1, INVALID_CHAR);
		WideCharToMultiByte(CP_UTF8, 0, src.c_str(), -1, &result[0], nRequiredSize, NULL, NULL);
		return result;
	}
}

namespace EncodingUtils
{
	const char * STR_HEX_CHARS = "0123456789ABCDEF";

	std::string URLEncode(const std::wstring & strIn)
	{
		const std::string strUTF8In = CommonUtil::UCS2toUTF8(strIn);
		return URLEncode(strUTF8In);
	}

	std::string URLEncode(const std::string & strUTF8In)
	{
		std::string strOut;

		//const string strUTF8In = CommonUtil::UCS2toUTF8(strIn);

		size_t i = 0;

		while (i < strUTF8In.length())
		{
			// HACK: CR10720 - instead of finding out which characters we *should* encode by walking a string,
			// it would be more accurate and efficient to compare each character to a known range of what *NOT*
			// to encode.  See RFC1738, Section 2.2.
			// We do *not* want to encode:  { x30 - x7a, x27-x2e, x21, x24 }
			// We *do* want to encode: { < x27 (except x21, x24), > 0x2e (except x5f) )
			//
			unsigned char ch = static_cast<unsigned char>(strUTF8In[i]);
			if (
				((ch < 0x41) || (ch > 0x5a)) &&	// not alphabetic (A-Z)
				((ch < 0x61) || (ch > 0x7a)) &&	// not alphabetic (a-z)
				((ch < 0x30) || (ch > 0x39)) &&	// not numeric
				((ch < 0x27) || (ch > 0x2a)) &&	// range of RFC specified non-encoded
				((ch < 0x2c) || (ch > 0x2e)) &&	// range of RFC specified non-encoded
				(ch != 0x21) &&	// three more stragglers to not encode that are outside above ranges
				(ch != 0x24) &&
				(ch != 0x5f) &&
				(ch != 0x2f) 	// this is added because our system of string management is based upon slashes; it is non-compliant but should NOT cause browsers problems and saves us a lot of recoding!
				)
			{
				char tz2[] =
				{
					'%',
					STR_HEX_CHARS[(ch >> 4) & 0x0F],
					STR_HEX_CHARS[ch & 0x0F],
				};
				strOut.append(tz2, 3);
			}
			else
			{
				strOut += static_cast<wchar_t>(strUTF8In[i]);
			}
			++i;
		}

		return strOut;
	}
}