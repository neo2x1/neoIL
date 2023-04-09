#include <iostream>
#include <fstream>
#include <vector>
#include "../hdr/Lexer.hpp"
int main()
{	//optimalisation
	std::ios::sync_with_stdio(false);
	//getting the file
	std::string str;
	std::cout << "Paste path where your file is:";
	std::cin >> str;
	std::ifstream programFile; programFile.open(str);
	//Lexer

	std::vector<Token> lexedFile;
	return 0;
}