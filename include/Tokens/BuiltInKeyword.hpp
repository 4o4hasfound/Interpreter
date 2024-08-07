#pragma once
#include <regex>
#include <memory>
#include <string>

#include "Token.hpp"
#include "GenerateRegex.hpp"
#include "Container/BidirectionalUnorderedMap.hpp"

class BuiltInKeyword : public Token {
public:
	enum KeywordType {
		VarVarVar,
		VarVarConst,
		VarConstVar,
		VarConstConst,
		ConstVarVar,
		ConstVarConst,
		ConstConstVar,
		ConstConstConst,
		If,
		Else,
		Return,
		Break,
		Continue,
		Function,
		True,
		False,
		Maybe,
		Print,
		Previous,
		Current,
		Reverse,
		Noop
	};
	BuiltInKeyword(KeywordType keywordType);

	virtual std::wstring str() const override;

	static std::unique_ptr<Token> getToken(std::wstring::const_iterator& start, std::wstring::const_iterator& end, Token *previousToken);
	static BidirectionalUnorderedMap<std::wstring, KeywordType> stringTokenMap;
	static std::vector<std::wstring> keywordRegexes;
private:
	static std::wregex s_regex;
	static std::wregex s_functionRegex;

	static std::wregex compileRegex();
};