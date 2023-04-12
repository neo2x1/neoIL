#include <iostream>
#include <fstream>
#include <vector>

#include "../hdr/Lexer.hpp"
#include "../hdr/Token.h"

int main()
{	//optimalisation
	std::ios::sync_with_stdio(false);
	//getting the file
	std::string str;
	std::cout << "Paste path where your file is:";
	std::cin >> str;
	std::ifstream programFile; programFile.open(str);
	
	//lexer lexes whole file
	std::string line;
	std::getline(std::cin, line);
	while (std::getline(programFile, line)) {
		lexer::Lex(line, lexer::line);
		for (int i = 0; i < lexer::line.size(); i++)
		lexer::output.push_back(lexer::line);
	}
	for (int j = 0; j < lexer::output.size(); j++) {
		for (int i = 0; i < lexer::output[j].size(); i++) {
			std::cout << lexer::output[j][i].type << " " << lexer::output[j][i].value << " , ";
		}
	}
	programFile.close();

	return 0;
}