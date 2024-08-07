#include <regex>
#include <memory>
#include <iostream>
#include "Parser.hpp"

int main() {
	Parser parser;
	parser.parseFile("program.txt");
	//parser.debugTokens();
}