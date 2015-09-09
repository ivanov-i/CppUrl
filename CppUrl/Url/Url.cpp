#include "stdafx.h"
#include <string>
#include "Url.h"

Url::Url(std::wstring str)
{
	if(str.empty())
		throw std::invalid_argument("the URL string is empty");
	Host = str;
}
