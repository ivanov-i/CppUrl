#pragma once
#include <string>

class Url
{
public:
	explicit Url(std::wstring str);
	std::wstring Host;
};
