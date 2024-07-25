#include "Tokens/StringLiteral.hpp"

StringLiteralToken::StringLiteralToken(const std::wstring& value)
	: Token(TokenType::StringLiteral)
	, literalValue(value) {

}
