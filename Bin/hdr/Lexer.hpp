#pragma once
#include <string>
#include <vector>
#include "../hdr/Token.h"
namespace lexer
{
	std::vector<std::vector<Token>> output;
	std::vector<Token> line;
	// gets string and gives it to the output
	void Lex(std::string str, std::vector<Token> tokens);
	// this function Lexes for Keywords Literals and names (used in Lex)
}