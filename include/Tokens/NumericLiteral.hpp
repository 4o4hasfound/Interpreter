#pragma once
#include <regex>
#include <memory>
#include <string>
#include <sstream>

#include "Token.hpp"
#include "Tokens/Operator.hpp"
#include "Tokens/Delimiter.hpp"

#include "GenerateRegex.hpp"
#include "Container/BidirectionalUnorderedMap.hpp"

class NumericLiteral : public Token {
public:
	enum NumericLiteralType {
		Interger,
		Float
	};
	NumericLiteral(NumericLiteralType literalType, double value);

	double literalValue;

	virtual std::wstring str() const override;

	static std::unique_ptr<Token> getToken(std::wstring::const_iterator& start, std::wstring::const_iterator& end, Token* previousToken);
	static std::vector<std::pair<std::wregex, NumericLiteralType>> regexTokenList;
};