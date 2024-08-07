#pragma once
#include <regex>
#include <memory>
#include <string>
#include <sstream>

#include "Token.hpp"
#include "GenerateRegex.hpp"
#include "Container/BidirectionalUnorderedMap.hpp"

class Delimiter : public Token {
public:
	enum DelimiterType {
		LParen,
		RParen,
		LBracket,
		RBracket,
		LCurlyBracket,
		RCurlyBracket,
		Comma
	};
	Delimiter(DelimiterType delimiterType);

	virtual std::wstring str() const override;

	static std::unique_ptr<Token> getToken(std::wstring::const_iterator& start, std::wstring::const_iterator& end, Token *previousToken);
	static BidirectionalUnorderedMap<std::wstring, DelimiterType> stringTokenMap;
private:
	static std::wregex s_regex;

	static std::wregex compileRegex();
};