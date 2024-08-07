#include "Parser.hpp"

Parser::Parser()
	: m_ast(m_tokens), m_lexer(m_tokens) {

}

void Parser::parseFile(const std::string& filename) {
	std::wifstream file;
	file.exceptions(std::ifstream::failbit);
	file.open(filename);

	std::wstringstream wss;
	wss << file.rdbuf();
	m_lexer.tokenize(wss.str());
	m_ast.build();
}

void Parser::parseString(const std::wstring& input) {
	m_lexer.tokenize(input);
}

void Parser::debugTokens() {
	for (const auto& token : m_tokens) {
		std::wcout << token->str() << "\n";
	}
}
