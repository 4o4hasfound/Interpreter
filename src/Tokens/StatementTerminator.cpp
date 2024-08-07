#include "Tokens/StatementTerminator.hpp"

std::vector<std::pair<std::wregex, StatementTerminator::TerminatorType>> StatementTerminator::regexTokenList{ {
	{generateRegex({LR"(^(\!+))"}, 0), StatementTerminator::ExclamationMark},
	{generateRegex({LR"(^(\?+))"}, 0), StatementTerminator::QuestionMark}
} };
std::wregex StatementTerminator::s_regex = compileRegex();

StatementTerminator::StatementTerminator(TerminatorType terminatorType, int terminatorCount)
	: Token(Token::StatementTerminator, terminatorType)
	, count(terminatorCount) {

}

std::wstring StatementTerminator::str() const {
	std::wstringstream ret;
	switch (valueType) {
	case TerminatorType::ExclamationMark:
		for (int i = 0; i < count; ++i) {
			ret << L'!';
		}
		return ret.str();
	case TerminatorType::QuestionMark:
		for (int i = 0; i < count; ++i) {
			ret << L'?';
		}
		return ret.str();
	}
	return L"";
}

std::unique_ptr<Token> StatementTerminator::getToken(std::wstring::const_iterator& start, std::wstring::const_iterator& end, Token* previousToken) {
	std::wsmatch match;
	for (const auto& [regex, tokenType] : regexTokenList) {
		if (std::regex_search(start, end, match, regex)) {
			start = match.suffix().first;
			return std::make_unique<StatementTerminator>(tokenType, match[0].length());
		}
	}
	return nullptr;
}

std::wregex StatementTerminator::compileRegex() {
	return generateRegex({ L"!+" }, 0);
}
