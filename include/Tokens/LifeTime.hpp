#pragma once
#include <regex>
#include <memory>
#include <string>
#include <sstream>

#include "Token.hpp"
#include "GenerateRegex.hpp"

class LifeTime : public Token {
public:
	enum LifeTimeType {
		Line,
		Second,
		Scope
	};
	LifeTime(LifeTimeType lifetimeType, double value);

	double lifetimeValue;

	virtual std::wstring str() const override;

	static std::unique_ptr<Token> getToken(std::wstring::const_iterator& start, std::wstring::const_iterator& end, Token *previousToken);
	static std::vector<std::pair<std::wregex, LifeTimeType>> regexTokenList;
};