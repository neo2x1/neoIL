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
	// lexer lexes whole file
	std::string line;
	while (std::getline(programFile, line)) {
		lexer::Lex(line, lexer::line);
		lexer::output.push_back(lexer::line);
	}
	std::cout << "{";
	for (int i = 0; i < lexer::output.size(); i++) {
		for (int j = 0; j < lexer::output[i].size(); j++) {
			std::cout << lexer::output[i][j].type << ":" << lexer::output[i][j].value << ", ";
		}
	}
	std::cout << "}";
	programFile.close();

	return 0;
}