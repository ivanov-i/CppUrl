#pragma once
#include <string>
#include <vector>

class Url
{
public:
	explicit Url(std::wstring str);
	std::wstring Scheme;
	std::wstring Authority;
	std::wstring Path;
	std::wstring Fragment;
	typedef std::vector<std::pair<std::wstring, std::wstring>> QueryArgs;
	QueryArgs Query;
};
