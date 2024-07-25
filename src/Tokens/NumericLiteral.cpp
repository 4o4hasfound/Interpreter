#include "Tokens/NumericLiteral.hpp"

NumericLiteralToken::NumericLiteralToken(std::int64_t value)
	: Token(TokenType::NumericLiteral)
	, literalValue(value)
	, literalType(NumericLiteralType::Interger) {

}
NumericLiteralToken::NumericLiteralToken(double value)
	: Token(TokenType::NumericLiteral)
	, literalValue(value)
	, literalType(NumericLiteralType::Double) {

}

