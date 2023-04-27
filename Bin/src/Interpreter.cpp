#include "../hdr/interpreter.h"
#include "../hdr/Token.h"
#include "../hdr/Lexer.hpp"

#include <vector>
#include <iostream>
#include <algorithm>
#include "../Repos/tinyexpr.h"

namespace interpreter 
{
	std::vector<Token> variables;
}


void interpreter::print(std::vector<Token> Tokens, int i) {
	for (int j = 1; j < Tokens.size(); j++)
	{
		if (Tokens[j].type == "keyword")
		{
			std::cout << "Err: Invalid syntax near line:" << i + 1;
			std::cin >> i;
			exit(-1);
		}
		else {
			if (Tokens[j].type == "name")
			{
				std::string varVal = interpreter::getVarVal(interpreter::variables, Tokens[j].value, i);
				std::cout << varVal;
			}
			else {
				if (Tokens[j].type == "operation")
				{
					std::string opVal = interpreter::doOperation(Tokens[j].value, i);
					std::cout << opVal;
				}
				else 
				{
					if (Tokens[j].value[0] == '\"') 
					{
						Tokens[j].value.erase(0,1);
						Tokens[j].value.pop_back();
					}
					
					if (Tokens[j].value == "clear")
					{
							system("cls");
							continue;
					}
					std::cout << Tokens[j].value;
				}
					
			}
		}
	}
	std::cout << "\n";
}


void interpreter::createVar(std::vector <Token> Tokens, int i, std::vector<Token>& variables)
{
	bool isSafe = false;
	
	if (Tokens[1].type == "name" && Tokens[2].type == "operator" && Tokens[2].value == "=") 
	{
		if (Tokens[3].type == "literal")
		{
			isSafe = true;
			variables.emplace_back(Tokens[1].value, Tokens[3].value);
			return;
		}
		else
		{
			if (Tokens[3].type == "operation")
			{
				
				isSafe = true;
				variables.emplace_back(Tokens[1].value, interpreter::doOperation(Tokens[3].value, i));
				return;
			}
			else 
			{
				if (Tokens[3].type == "name")
				{
					isSafe = true;
					variables.emplace_back(Tokens[1].value, interpreter::getVarVal(interpreter::variables, Tokens[3].value, i));
					return;
				}
			}
		}
	}

	if (isSafe == false) {
		std::cout << "Err: Invalid syntax near line:" << i + 1;
		std::getchar();
		exit(-1);
	}
}

std::string interpreter::getVarVal(std::vector<Token> variables, std::string name, int i) 
{

	for (int j = 0; j < variables.size(); j++) 
	{
		if (variables[j].type == name) 
		{
			if (variables[j].value[0] == '\"')
			{
				variables[j].value.erase(0, 1);
				variables[j].value.pop_back();
			}
			return variables[j].value;
		}
	}
	std::cout << "Err: Invalid name at line:" << i + 1;
	exit(-1);
}
std::string interpreter::getVarValN(std::vector<Token> variables, std::string name, int i)
{
	for (int j = 0; j < variables.size(); j++)
	{
		if (variables[j].type == name)
		{
			return variables[j].value;
		}
	}
	std::cout << "Err: Invalid name at line:" << i + 1;
	exit(-1);
}

std::string interpreter::doOperation(std::string operation, int i)
{
	std::string collect = "";
	std::string operationLexed;
	bool stringOperation = false;
	bool ending = true;
	// this for searches for strings and turn them into coresponding variables
	for (int j = 1; j < operation.size() - 1; j++) 
	{
		if (isalpha(operation[j])) 
		{
			for (int k = j; k < operation.size() - 1; k++)
			{
				bool breakfrom = false;
				if(!isalpha(operation[k])) 
				{
					std::string a = interpreter::getVarVal(interpreter::variables, collect, i);
					if (a[0] == '\"') 
					{
						stringOperation = true;
						break;
					}
					operationLexed.append(a);
					collect.clear();
					break;
				}
				if (!breakfrom) {
					collect += operation[k];
				}

			}
			continue;
		}
		operationLexed += operation[j];
		if (operation[j] == '\"') {
			stringOperation = true;
			break;
		}
	}
	if (stringOperation == true)
	{
		std::string collect = "";
		std::string save = "";
		bool ending = true;
		for (int  j = 0; j < operation.size() - 1; j++)
		{
			if (operation[j] == '-' || operation[j] == '/' || operation[j] == '%' || operation[j] == '(' || operation[j] == ')' || operation[j] == '^' || operation[j] == '*')
			{
				std::cout << "Err: Invalid string operation at line: " << i + 1;
				std::getchar();
				exit(-1);
			}
			if (operation[j] == '\"')
			{
				for (int k = j + 1; k < operation.size() - 1; k++)
				{
					ending = false;
					if (operation[k] == '\"')
					{
						ending = true;
						save.append(collect);
						j = k + 1;
						collect.clear();
						break;
					}
					collect += operation[k];
				}
			}
			if (isdigit(operation[j]))
			{
				for (int k = j; k < operation.size() - 1; k++)
				{
					if (!isdigit(operation[k]))
					{
						save.append(collect);
						j = k ;
						collect.clear();
						break;
					}
					collect += operation[k];
				}
			}
			// the same thing as in previous
			if (isalpha(operation[j]))
			{	
				ending = false;
				for (int k = j; k < operation.size() - 1; k++)
				{	
					if (!isalpha(operation[k]))
					{ 
						ending = true;
						save.append(interpreter::getVarVal(interpreter::variables, collect, i));
						j = k + 1;
						collect.clear();
						break;
					}
					collect += operation[k];
				}
			}
			if (operation[j] == '+')
			{
				for (int l = j; l < operation.size() - 1; l++)
				{
					if (operation[j] == '\"')
					{
						
						for (int k = l + 1; k < operation.size() - 1; k++)
						{
							if (operation[k] == '\"')
							{
								save.append(collect);
								j = k + 1;
								collect.clear();
								break;
							}
							collect += operation[k];
						}
						break;
					}
					if (isdigit(operation[j]))
					{
						for (int k = j + 1; k < operation.size() - 1; k++)
						{

							if (!isdigit(operation[k]))
							{
								save.append(collect);
								j = k + 1;
								collect.clear();
								break;
							}
							collect += operation[k];
						}
						break;
					}
				}
				continue;
			}

		}
		
		if (!ending) {
			save.append(interpreter::getVarVal(interpreter::variables, collect, i));
		}
		else
			save.append(collect);
		return save;
	}
		
	bool digit = true;
	for (int j = 0; j < collect.length(); j++) {
			if (!isdigit(collect[j]))
				digit = false;
	}
	if (!digit) {
		operationLexed.append(interpreter::getVarVal(interpreter::variables, collect, i));
	}
	const char* temptext = operationLexed.c_str();
	float a = te_interp(temptext, 0);
	if (a == NAN) {
		std::cout << "Err: Invalid operation at line: " << i + 1;
		std::getchar();
		exit(-1);
	}
	return std::to_string(int(te_interp(temptext, 0)));
	delete temptext;
}

void interpreter::alterVar(std::vector <Token> Tokens, int i, std::vector<Token>& variables)
{
	int placeInVec = variables.size()+1;

	for (int j = 0; j < variables.size(); j++)
	{
		if (variables[j].type == lexer::output[i][0].value) {
			placeInVec = j;
			break;
		}
	}
	if (placeInVec < variables.size()) 
	{
		if (Tokens[0].type == "name" && Tokens[1].type == "operator" && Tokens[1].value == "=")
		{
			if (Tokens[2].type == "literal")
			{
				variables[placeInVec].value = Tokens[2].value;
				return;
			}
			if (Tokens[2].type == "operation")
			{
				variables[placeInVec].value = interpreter::doOperation(Tokens[2].value, i);
				return;
			}
			if (Tokens[2].type == "name")
			{
				variables[placeInVec].value = interpreter::getVarVal(interpreter::variables, Tokens[2].value, i);
				return;
			}
		}
	}
	std::cout << "Err: Invalid name near line:" << i + 1;
	std::getchar();
	exit(-1);
}

void interpreter::input(std::vector <Token> Tokens, int i, std::vector<Token>& variable)
{
	if (Tokens[1].type == "name")
	{
		int placeInVec = variables.size();
		for (int j = 0; j < variables.size(); j++)
		{
			if (variable[j].type == lexer::output[i][1].value) {
				placeInVec = j;
				break;
			}
		}
		if (placeInVec == variable.size()) 
		{
			std::cout << "Err: Invalid name near line:" << i + 1;
			std::getchar();
			exit(-1);
		}
		std::string value;
		std::cin >> value;
		if (value[0] == '~') {
			if (value[value.size()-1] == '~') 
			{
				variable[placeInVec].value = interpreter::doOperation(Tokens[2].value, i);
				return;
			}
			else 
			{
				std::cout << "Err: Expected ~ at line:" << i + 1;
				std::getchar();
				exit(-1);
			}
		}
		for (int j = 0; j < value.size(); j++) 
		{
			if (!isdigit(value[j])) 
			{
				break;
			}
			if (j == value.size() - 1) 
			{
				variable[placeInVec].value = value;
				return;
			}
		}
		variable[placeInVec].value = '\"' + value + '\"';
	}
	else
	{
		std::cout << "Err: Invalid syntax near line:" << i + 1;
		std::getchar();
		exit(-1);
	}
}

void interpreter::eval(std::vector<std::vector<Token>> Tokens, int i, int& startI)
{
	int whereToStopi = startI;
	int wTSI = startI;
	//if leftside operators rightside

	//search where it needs to start
	int aN = 0;
	int bN = 0;
	bool isaempty = true;
	bool isbempty = true;
	std::string a;
	std::string b;
	std::string operators;
	int bracketsCount = 0;
	int whereToStarti = 0;
	int whereToStartj = 0;
	for (int j = i; j < Tokens.size(); j++)
	{

		for (int k = 0; k < Tokens[j].size(); k++) {
			if (Tokens[j][k].value == "{") { bracketsCount++; wTSI = j + 1; break; }
		}
		if (wTSI > 0)
		{
			break;
		}

	}
	wTSI--;
	//count brackets to make sure it skips when if is false
	bool exitl = false;
	for (int j = wTSI + 1; j < Tokens.size(); j++)
	{
		for (int k = 0; k < Tokens[j].size(); k++) {
			if (Tokens[j][k].value == "{") bracketsCount++;
			if (Tokens[j][k].value == "}") bracketsCount--;
			if (bracketsCount == 0)
			{
				whereToStopi = j;
				exitl = true;
				break;
			}
		}
		if (exitl == true) {
			break;
		}
	}
	if (bracketsCount != 0)
	{
		std::cout << "Err: Missing { or }";
		std::getchar();
		exit(0);
	}
	// check if leftside and rightside is operation or name to get value or do an operation
	if (Tokens[i][1].type == "operation")
	{
		std::string c = interpreter::doOperation(Tokens[i][1].value, i);
		if (c[0] != '\"') {
			aN = std::stoi(c);
			isaempty = false;
		}
		else {
			a = c;
		}
	}
	if (Tokens[i][1].type == "name")
	{
		std::string c = interpreter::getVarValN(interpreter::variables, Tokens[i][1].value, i);
		if (c[0] != '\"') {
			aN = std::stoi(c);
			isaempty = false;
		}
		else {
			a = c;
		}
	}
	if (Tokens[i][1].type == "literal")
	{
		std::string c = Tokens[i][1].value;
		if (c[0] != '\"')
		{
			aN = std::stoi(c);
			isaempty = false;
		}
		else
		{
			a = c;
		}

	}
	if (Tokens[i][3].type == "operation")
	{
		std::string c = interpreter::doOperation(Tokens[i][3].value, i);
		if (c[0] != '\"') {
			bN = std::stoi(c);
			isbempty = false;
		}
		else {
			b = c;
		}
	}
	if (Tokens[i][3].type == "name")
	{
		std::string c = interpreter::getVarValN(interpreter::variables, Tokens[i][3].value, i);
		if (c[0] != '\"') {
			bN = std::stoi(c);
			isbempty = false;
		}
		else {
			b = c;
		}
	}
	if (Tokens[i][3].type == "literal")
	{
		std::string c = Tokens[startI][3].value;
		if (c[0] != '\"')
		{
			bN = std::stoi(c);
			isbempty = false;
		}
		else
		{
			b = c;
		}
	}
	//check for type
	if (( !isbempty && isaempty ) || (!isaempty && isbempty ))
	{
		startI = whereToStopi;
	}
	// eval statement
	if (!isaempty)
	{
		if (Tokens[startI][2].value == "=")
		{
			if (aN == bN) {
				startI = wTSI;
				return;
			}
			else {
				startI = whereToStopi;
				return;
			}
		}
		if (Tokens[startI][2].value == ">")
		{
			if  (aN > bN) {
				startI = wTSI;
				return;
			}
			else {
				startI = whereToStopi;
				return;
			}
		}
		if (Tokens[startI][2].value == "<")
		{
			if (aN < bN) {
				startI = wTSI; return;
			}
			else { startI = whereToStopi; return; }
		}
		if (Tokens[startI][2].value == "|")
		{
			if (aN != bN) {
				startI = wTSI; return;
			}
			else {
				startI = whereToStopi;
				return;
			}

		}
	}
	else
	{
		if (Tokens[startI][2].value == "=")
		{
			if (a == b) {
				startI = wTSI;
				return;
			}
			else {
				startI = whereToStopi;
				return;
			}
		}
		if (Tokens[startI][2].value == ">")
		{
			if (a > b) {
				startI = wTSI;
				return;
			}
			else {
				startI = whereToStopi;
				return;
			}
		}
		if (Tokens[startI][2].value == "<")
		{
			if (a < b) {
				startI = wTSI; return;
			}
			else { startI = whereToStopi; return; }
		}
		if (Tokens[startI][2].value == "|")
		{
			if (a != b) {
				startI = wTSI; return;
			}
			else {
				startI = whereToStopi;
				return;
			}

		}
	}
}
void interpreter::whileS(std::vector<std::vector<Token>> Tokens, int i, int& startI, bool& inLoop, int& whereToStopi, int &wTSI)
{
	inLoop = true;
	whereToStopi = startI;
	wTSI = startI;
	//if leftside operators rightside

	//search where it needs to start
	int aN = 0;
	int bN = 0;
	bool isaempty = true;
	bool isbempty = true; 
	std::string a;
	std::string b;
	int bracketsCount = 0;
	for (int j = i; j < Tokens.size(); j++)
	{

		for (int k = 0; k < Tokens[j].size(); k++) {
			if (Tokens[j][k].value == "{") { bracketsCount++; wTSI = j + 1; break; }
		}
		if (wTSI > 0)
		{
			break;
		}

	}
	wTSI--;
	//count brackets to make sure it skips when if is false
	bool exitl = false;
	for (int j = wTSI + 1; j < Tokens.size(); j++)
	{
		for (int k = 0; k < Tokens[j].size(); k++) {
			if (Tokens[j][k].value == "{") bracketsCount++;
			if (Tokens[j][k].value == "}") bracketsCount--;
			if (bracketsCount == 0)
			{
				whereToStopi = j;
				exitl = true;
				break;
			}
		}
		if (exitl == true) {
			break;
		}
	}
	if (bracketsCount != 0)
	{
		std::cout << "Err: Missing { or }";
		std::getchar();
		exit(0);
	}
	// check if leftside and rightside is operation or name to get value or do an operation
	if (Tokens[i][1].type == "operation")
	{
		std::string c = interpreter::doOperation(Tokens[i][1].value, i);
		if (c[0] != '\"') {
			aN = std::stoi(c);
			isaempty = false;
		}
		else {
			a = c;
		}
	}
	if (Tokens[i][1].type == "name")
	{
		std::string c = interpreter::getVarValN(interpreter::variables, Tokens[i][1].value, i);
		if (c[0] != '\"') {
			aN = std::stoi(c);
			isaempty = false;
		}
		else {
			a = c;
		}
	}
	if (Tokens[i][1].type == "literal")
	{
		std::string c = Tokens[i][1].value;
		if (c[0] != '\"')
		{
			aN = std::stoi(c);
			isaempty = false;
		}
		else
		{
			a = c;
		}

	}
	if (Tokens[i][3].type == "operation")
	{
		std::string c = interpreter::doOperation(Tokens[i][3].value, i);
		if (c[0] != '\"') {
			bN = std::stoi(c);
			isbempty = false;
		}
		else {
			b = c;
		}
	}
	if (Tokens[i][3].type == "name")
	{
		std::string c = interpreter::getVarValN(interpreter::variables, Tokens[i][3].value, i);
		if (c[0] != '\"') {
			bN = std::stoi(c);
			isbempty = false;
		}
		else {
			b = c;
		}
	}
	if (Tokens[i][3].type == "literal")
	{
		std::string c = Tokens[startI][3].value;
		if (c[0] != '\"')
		{
			bN = std::stoi(c);
			isbempty = false;
		}
		else
		{
			b = c;
		}
	}
	//check for type
	if ((!isbempty && isaempty) || (!isaempty && isbempty))
	{
		startI = whereToStopi;
	}
	// eval statement
	if (!isaempty)
	{
		if (Tokens[startI][2].value == "=")
		{
			if (aN == bN) {
				inLoop = true;
			}
			else {
				inLoop = false;
			}
		}
		if (Tokens[startI][2].value == ">")
		{
			if (aN > bN) {
				inLoop = true;
			}
			else {
				inLoop = false;
			}
		}
		if (Tokens[startI][2].value == "<")
		{
			if (aN < bN) {
				inLoop = true;
			}
			else {
				inLoop = false;
			}
		}
		if (Tokens[startI][2].value == "|")
		{
			if (aN != bN) {
				inLoop = true;
			}
			else {
				inLoop = false;
			}

		}
	}
	else
	{
		if (Tokens[startI][2].value == "=")
		{
			if (a == b) {
				inLoop = true;
			}
			else {
				inLoop = false;
			}
		}
		if (Tokens[startI][2].value == ">")
		{
			if (a > b) {
				inLoop = true;
			}
			else {
				inLoop = false;	
			}
		}
		if (Tokens[startI][2].value == "<")
		{
			if (a < b) {
				inLoop = true;
			}
			else {
				inLoop = false;
			}
		}
		if (Tokens[startI][2].value == "|")
		{
			if (a != b) {
				inLoop = true;
			}
			else {
				inLoop = false;
			}

		}
	}
	
}
