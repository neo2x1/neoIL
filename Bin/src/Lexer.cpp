#include <string>
#include <iostream>
#include <cctype>
#include "../hdr/Token.h"
#include "../hdr/Lexer.hpp"
namespace lexer 
{
	std::vector<std::vector<Token>> output;
	std::vector<Token> line;
}
void lexer::Lex(std::string str, std::vector<Token> &tokens)
{
	std::string couple = ""; 
	for (int i = 0; i < str.length(); i++) 
	{
		switch (str[i])
		{	
			case '+':
				lexer::SaveCouple(line, couple);
				tokens.emplace_back("operator", "+");
				break;
			case '-':
				lexer::SaveCouple(line, couple);
				tokens.emplace_back("operator", "-");
				couple = "";
				break;
			case '*':
				lexer::SaveCouple(line, couple);
				tokens.emplace_back("operator", "*");
				couple = "";
					break;
			case '/':
				lexer::SaveCouple(line, couple);
				tokens.emplace_back("operator", "/");
				couple = "";
					break;
			case '(':
				lexer::SaveCouple(line, couple);
				tokens.emplace_back("operator", "(");
				couple = "";
					break;
			case ')':
				lexer::SaveCouple(line, couple);
				tokens.emplace_back("operator", ")");
				couple = "";
					break;
			case '^':
				lexer::SaveCouple(line, couple);
				tokens.emplace_back("operator", "^");
				couple = "";
					break;
			case '%':
				lexer::SaveCouple(line, couple);
				tokens.emplace_back("operator", "%");
				couple = "";
					break;
			case '!':
				lexer::SaveCouple(line, couple);
				tokens.emplace_back("operator", "!");
				couple = "";
					break;
			case '=':
				lexer::SaveCouple(line, couple);
				tokens.emplace_back("operator", "=");
				couple = "";
					break;
			case '{':
				lexer::SaveCouple(line, couple);
				tokens.emplace_back("operator", "{");
				couple = "";
				break;
			case '}':
				lexer::SaveCouple(line, couple);
				tokens.emplace_back("operator", "}");
				couple = "";
				break;

			/*
			*	literal string string: ignores operators literals
			*	so:
			*	[literal:"a=b", ...]
			*	wouldn't be:
			*	[literal:"a, operator:=, literal:b", ...]
			*/
			case '~':
				lexer::Lexline(str, tokens, '~', "operation", i);
					break;
			case '\"':
				lexer::Lexline(str, tokens, '\"', "literal", i);
				break;
					
			default:
				if (couple != "" && str[i] == ' ')
				{
					lexer::SaveCouple(line, couple);
				}
				couple += str[i];
		}
	}
	lexer::SaveCouple(line, couple);
}
void lexer::Lexline(std::string str2, std::vector<Token> &tokens, char endchar, std::string type, int &beg) 
{
	bool isEnd = false;
	std::string couple2 = "";
	couple2+=endchar;
	beg++;
	
	for (int j = beg; j < str2.length(); j++)
	{
		couple2 += str2[j];
		if (str2[j] == endchar)
		{
			isEnd = true;
			beg = j;
			tokens.emplace_back(type, couple2);
			break;
		}
	}
	if(isEnd == false)
	{
		std::cout << "Err: expected " << endchar << " somewhere near [ " << str2 << " ]";
		exit(-1);
	}
}
void lexer::SaveCouple(std::vector<Token> &tokens, std::string &couple)
{
	bool testNum = true;
	for (int j = 0; j < couple.length(); j++) {
		if (!std::isdigit(couple[j]) || couple[j] == '.') { testNum = false; break; }
	}
	if (couple == "True" || couple == "False" || testNum == true)
	{
		tokens.emplace_back("literal", couple);
		couple = "";
		return;
	}
	if (couple == "if" || couple == "else" || couple == "func" || couple == "print" || couple == "while" || couple == "let" || couple == "input")
	{
		tokens.emplace_back("keyword", couple);
		couple = "";
		return;
	}
	tokens.emplace_back("name", couple);
	couple = "";
	return;
}