#pragma once
#include <string>

class Url
{
public:
	explicit Url(std::wstring str);
	std::wstring Scheme;
	std::wstring Authority;
	std::wstring Path;
	std::wstring Query;
	std::wstring Fragment;
};
