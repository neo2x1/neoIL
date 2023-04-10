#pragma once
#include <string>
struct Token
{
	Token(std::string ty, std::string val);
	std::string type;
	std::string value;
};