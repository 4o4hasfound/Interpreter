#pragma once
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <string.h>
#include <iostream>

#include "Token.hpp"
#include "Tokens/LifeTime.hpp"
#include "Tokens/Operator.hpp"
#include "Tokens/Delimiter.hpp"
#include "Tokens/WhiteSpace.hpp"
#include "Tokens/Identifier.hpp"
#include "Tokens/StringLiteral.hpp"
#include "Tokens/StringLiteral.hpp"
#include "Tokens/NumericLiteral.hpp"
#include "Tokens/BuiltInKeyword.hpp"
#include "Tokens/StatementTerminator.hpp"

#include "AST.hpp"
#include "Lexer.hpp"

class Parser {
public:
	Parser();

	void parseFile(const std::string& filename);
	void parseString(const std::wstring& input);

	void debugTokens();
private:
	std::vector<std::unique_ptr<Token>> m_tokens;
	AST m_ast;
	Lexer m_lexer;
};