#pragma once
#include <regex>
#include <memory>
#include <string>
#include <sstream>

#include "Token.hpp"
#include "GenerateRegex.hpp"
#include "Container/BidirectionalUnorderedMap.hpp"

class StatementTerminator: public Token {
public:
	enum TerminatorType {
		ExclamationMark,
		QuestionMark
	};
	StatementTerminator(TerminatorType terminatorType, int terminatorCount);

	int count;

	virtual std::wstring str() const override;

	static std::unique_ptr<Token> getToken(std::wstring::const_iterator& start, std::wstring::const_iterator& end, Token *previousToken);
	static std::vector<std::pair<std::wregex, TerminatorType>> regexTokenList;
private:
	static std::wregex s_regex;

	static std::wregex compileRegex();
};