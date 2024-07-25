#pragma once
#include <variant>

#include "Token.hpp"

enum class NumericLiteralType {
	Interger,
	Double
};

struct NumericLiteralToken : public Token {
	NumericLiteralToken(std::int64_t value);
	NumericLiteralToken(double value);

	NumericLiteralType literalType;
	std::variant<std::int64_t, double> literalValue;
};