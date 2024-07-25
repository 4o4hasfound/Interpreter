#pragma once
#include <any>

enum class TokenType {
	NumericLiteral,
	StringLiteral,
	Operator,
	DELIMITER,
	Identifier,
	BuiltInKeyWord
};

struct Token {
	TokenType type;

	Token(TokenType tokenType);
};
