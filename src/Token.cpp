#include "Token.hpp"

Token::Token(TokenType tokenType, int underLyingValueType)
	: type(tokenType), valueType(underLyingValueType) {

}

bool Token::isType(TokenType targetTokenType) const {
	return type == targetTokenType;
}

bool Token::isType(TokenType targetTokenType, int targetValueType) const {
	return type == targetTokenType && valueType == targetValueType;
}