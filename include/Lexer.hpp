#pragma once
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <string.h>
#include <iostream>

#include "Token.hpp"
#include "Tokens/Boolean.hpp"
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

class Lexer {
public:
	Lexer(std::vector<std::unique_ptr<Token>>& tokens);

	void tokenize(const std::wstring& input);
private:
	std::vector<std::unique_ptr<Token>>& m_tokens;
};