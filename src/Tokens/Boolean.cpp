#include "Tokens/Boolean.hpp"

std::vector<std::pair<std::wregex, Boolean::BooleanType>> Boolean::regexTokenList{ {
	{generateRegex({LR"(true)"}, 0, L"a-zA-Z"), BooleanType::True},
	{generateRegex({LR"(maybe)"}, 0, L"a-zA-Z"), BooleanType::Maybe},
	{generateRegex({LR"(false)"}, 0, L"a-zA-Z"), BooleanType::False},
} };

Boolean::Boolean(BooleanType booleanType)
	: Token(TokenType::Boolean) {

}

std::wstring Boolean::str() const {
	switch (valueType) {
	case Boolean::True:
		return L"true";
	case Boolean::Maybe:
		return L"maybe";
	case Boolean::False:
		return L"false";
	}
	return L"";
}

std::unique_ptr<Token> Boolean::getToken(std::wstring::const_iterator& start, std::wstring::const_iterator& end, Token* previousToken) {
	std::wsmatch match;
	for (const auto& [regex, tokenType] : regexTokenList) {
		if (std::regex_search(start, end, match, regex)) {
			start = match.suffix().first;
			return std::make_unique<Boolean>(tokenType);
		}
	}
	return nullptr;
}