#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <chrono>
#include <thread>

#include "../hdr/Lexer.hpp"
#include "../hdr/Token.h"
#include "../hdr/interpreter.h"
int main()
{	//optimalisation
	std::ios::sync_with_stdio(false);
	//getting the file
	std::cout << "          _           _____ _\n";
	std::cout << "     / \\ | |         |_   _| |\n";
	std::cout << "|\\/\\ |  \\| | ___  ___  | | | | /\\/|\n";
	std::cout << " \\/\\ | . ` |/ _ \\/ _ \\ | | | | /\\/\n";
	std::cout << "     | |\\  |  __/ (_) || |_| |___\n";
	std::cout << "     \\_| \\_/\\___|\\___/\\___/|_____|\n";
	std::string str;
	std::cout << "Paste path of your file: ";
	std::cin >> str;
	system("cls");
	//getting the file type
	if (str.substr(str.find_last_of('.') + 1, 3) == "nil")
	{
		std::ifstream programFile; programFile.open(str);
		if (!programFile.good()) {
			std::cout << "Err: wrong filetype or file couldn't be open";
			std::getchar();
			exit(-1);
		}
		//lexer lexes whole file
		while (std::getline(programFile, str)) {
			lexer::Lex(str, lexer::line);
			lexer::output.push_back(lexer::line);
		}
		programFile.close();
		str.clear();
		//parse tokens
		bool inLoop = false;
		int loopI,statementI=0;
		for (int i = 0; i < lexer::output.size(); i++)
		{
			if (inLoop && i == loopI) 
			{
				i = statementI;
			}
			if (lexer::output[i][0].value == "print") {
				interpreter::print(lexer::output[i], i);
			}
			if (lexer::output[i][0].value == "let") {
				interpreter::createVar(lexer::output[i], i, interpreter::variables);
			}
			if (lexer::output[i][0].value == "input") 
			{
				interpreter::input(lexer::output[i], i, interpreter::variables);
			}
			if (lexer::output[i][0].value == "while") {
					interpreter::whileS(lexer::output, i, i, inLoop, loopI, statementI);
			}
			if (lexer::output[i][0].type == "name") {
					interpreter::alterVar(lexer::output[i], i, interpreter::variables);
			}
			if (lexer::output[i][0].value == "if")
			{
				interpreter::eval(lexer::output, i, i);
			}
			if (lexer::output[i][0].value == "exit")
			{
				exit(0);
			}
			if (lexer::output[i][0].value == "delay")
			{
				std::this_thread::sleep_for(std::chrono::seconds(std::stoi(lexer::output[i][1].value)));
			}

		}
	}
	else
	{
		std::cout << "Err: wrong filetype or file couldn't be open";
		std::getchar();
		exit(-1);
	}
	return 0;
}