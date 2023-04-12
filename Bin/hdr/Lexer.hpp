#pragma once
#include <string>
#include <vector>
#include "../hdr/Token.h"
namespace lexer
{
	extern std::vector<std::vector<Token>> output;
	extern std::vector<Token> line;
	// gets string and gives it to the output
	void Lex(std::string str, std::vector<Token> &tokens);
	// this function Lexes entire line of code - used in " and ~
	void Lexline(std::string str, std::vector<Token>& tokens, char endchr, std::string type, int &beg);	
	// if an operator or " " this saves what was saved
	void SaveCouple(std::vector<Token>& tokens, std::string& couple);
}