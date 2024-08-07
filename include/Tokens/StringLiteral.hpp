#pragma once
#include <regex>
#include <string>

#include "Token.hpp"
#include "GenerateRegex.hpp"

class StringLiteral : public Token {
public:
	StringLiteral(const std::wstring& value);

	std::wstring literalValue;

	virtual std::wstring str() const override;

	static std::unique_ptr<Token> getToken(std::wstring::const_iterator& start, std::wstring::const_iterator& end, Token *previousToken);
private:
	static std::wregex s_regex;
};