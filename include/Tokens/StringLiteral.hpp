#pragma once
#include <string>

#include "Token.hpp"

struct StringLiteralToken : public Token {
	StringLiteralToken(const std::wstring& value);

	std::wstring literalValue;
};