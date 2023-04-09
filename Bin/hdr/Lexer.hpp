#pragma once
#include <string>
#include <vector>
namespace lexer
{
	std::vector<Token> output;
	std::vector<Token> Lex(std::string str);
	// this function Lexes for Keywords Literals and names
	std::vector<Token> KeyLitNam(std::string str);
}