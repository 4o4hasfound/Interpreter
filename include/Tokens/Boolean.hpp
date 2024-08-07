#pragma once
#include <regex>
#include <memory>
#include <string>
#include <sstream>

#include "Token.hpp"

#include "GenerateRegex.hpp"
#include "Container/BidirectionalUnorderedMap.hpp"


class Boolean : public Token {
public:
	enum BooleanType {
		True,
		Maybe,
		False
	};
	Boolean(BooleanType BooleanType);

	virtual std::wstring str() const override;

	static std::unique_ptr<Token> getToken(std::wstring::const_iterator& start, std::wstring::const_iterator& end, Token* previousToken);
	static std::vector<std::pair<std::wregex, BooleanType>> regexTokenList;
};