#pragma once
#include <vector>
#include <string>

#include "token.h"
namespace interpreter {
	extern std::vector<Token> variables;

	void print(std::vector<Token> Tokens, int i);

	void createVar(std::vector <Token> Tokens, int i, std::vector<Token> &variables);
	void alterVar(std::vector <Token> Tokens, int i, std::vector<Token> &variables);
	void input(std::vector <Token> Tokens, int i, std::vector<Token> &variable);
	void eval(std::vector<std::vector<Token>> Tokens, int i, int& tartI);
	void whileS(std::vector<std::vector<Token>> Tokens, int i, int& startI, bool& inLoop, int& whereToStopi, int& wTSI);
	std::string getVarVal(std::vector<Token> variables, std::string name, int i);
	std::string getVarValN(std::vector<Token> variables, std::string name, int i);
	std::string doOperation(std::string operation, int i);
	

}