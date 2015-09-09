#pragma once
#include <string>
#include <vector>

class Url
{
public:
	Url();
	explicit Url(std::string str);
	Url(const std::wstring& scheme, const std::wstring& authority, const std::wstring& path, const std::wstring& fragment, const std::vector<std::pair<std::wstring, std::wstring>>& query);
	std::string Compile() const;

	std::wstring Scheme;
	std::wstring Authority;
	std::wstring Path;
	std::wstring Fragment;
	typedef std::vector<std::pair<std::wstring, std::wstring>> QueryArgs;
	QueryArgs Query;
private:
	void Parse(const std::string& str);
};
