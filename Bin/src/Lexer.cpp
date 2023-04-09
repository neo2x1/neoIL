#include <string>

#include "../hdr/Lexer.hpp"
std::vector<Token> lexer::Lex(std::string str) 
{
	std::string couple;
	std::vector<Token> tokens;
	for (int i = 0; i < str.length(); i++) 
	{	//operators
		switch (str[i])
		{	
			case '+':
				tokens.emplace_back(Token::type::OPERATOR, "+");
				break;
			case '-':
				tokens.emplace_back(Token::type::OPERATOR, "-");
					break;
			case '*':
				tokens.emplace_back(Token::type::OPERATOR, "*");
					break;
			case '/':
				tokens.emplace_back(Token::type::OPERATOR, "/");
					break;
			case '(':
				tokens.emplace_back(Token::type::OPERATOR, "(");
					break;
			case ')':
				tokens.emplace_back(Token::type::OPERATOR, ")");
					break;
			case '^':
				tokens.emplace_back(Token::type::OPERATOR, "^");
					break;
			case '%':
				tokens.emplace_back(Token::type::OPERATOR, "%");
					break;
			case '!':
				tokens.emplace_back(Token::type::OPERATOR, "!");
					break;
			case '=':
				tokens.emplace_back(Token::type::OPERATOR, "=");
					break;
			/*
			*	literal string string: ignores operators literals
			*	so:
			*	[literal:"a=b", ...]
			*	wouldn't be:
			*	[literal:"a, operator:=, literal:b", ...]
			*/
			case '\"':
					couple += str;
					if (str[i] == '\"') 
					{
						tokens.emplace_back(Token::type::LITERAL, couple);
						couple = "";
						break;
					}
			default:
					
					break;
		}
	}
}

std::vector<Token> lexer::KeyLitNam(std::string str)
{
	
}