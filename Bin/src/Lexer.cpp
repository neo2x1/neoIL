#include <string>
#include <iostream>
#include "../hdr/Token.h"
#include "../hdr/Lexer.hpp"
#include "Token.cpp"
void lexer::Lex(std::string str, std::vector<Token> tokens)
{
	std::string couple;
	
	for (int i = 0; i < str.length(); i++) 
	{	//operators
		switch (str[i])
		{	
			case '+':
				tokens.emplace_back("operator","+");
				break;
			case '-':
				tokens.emplace_back("operator", "-");
					break;
			case '*':
				tokens.emplace_back("operator","*");
					break;
			case '/':
				tokens.emplace_back("operator","/");
					break;
			case '(':
				tokens.emplace_back("operator", "(");
					break;
			case ')':
				tokens.emplace_back("operator", ")");
					break;
			case '^':
				tokens.emplace_back("operator", "^");
					break;
			case '%':
				tokens.emplace_back("operator", "%");
					break;
			case '!':
				tokens.emplace_back("operator", "!");

					break;
			case '=':
				tokens.emplace_back("operator", "=");
					break;
			case '~':
				tokens.emplace_back("operator", "~");
				break;
			case '{':
				tokens.emplace_back("operator", "{");
				break;
			case '}':
				tokens.emplace_back("operator", "}");
				break;
			/*
			*	literal string string: ignores operators literals
			*	so:
			*	[literal:"a=b", ...]
			*	wouldn't be:
			*	[literal:"a, operator:=, literal:b", ...]
			*/
			case '\"':
					for(int j=i; j<str.length(); j++)
					{ 
						couple += str[j];
						if (str[j] == '\"') 
						{
							tokens.emplace_back("literal", couple);
							couple = "";
							i = j;
							break;
						}
					}
					//todo if not found found second "
			default:
				std::string numbers = "1234567890.";
				if (str[i] = ' ' && couple != "")
				{
					bool testNum = true;
					for (int j = 0; j < couple.length(); j++) {
						if (!numbers.find(couple[j])) { testNum = false; }
					}
					if (couple == "True" || couple == "False" || testNum)
					{
						tokens.emplace_back("literal", couple);
						couple = "";
						break;
					}
					if (couple == "if" || couple == "else" || couple == "func" || couple == "print" || couple == "while" ||  couple == "let" || couple == "input")
					{	
						tokens.emplace_back("keyword", couple);
						couple = "";
						break;
					}
						
				}
				if (couple = "" || str[i] != ' ' && couple != "")
				{
					couple += str[i];
				}
		}
	}
}