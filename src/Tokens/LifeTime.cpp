#include "Tokens/LifeTime.hpp"

std::vector<std::pair<std::wregex, LifeTime::LifeTimeType>> LifeTime::regexTokenList{ {
	{ generateRegex({LR"(^< *([-+]?[0-9]+) *>)"}, 0, L""), LifeTimeType::Line },
	{ generateRegex({LR"(^< *([-+]?[0-9]+(\.[0-9]*)?) *s *>)"}, 0, L""), LifeTimeType::Second },
	{ generateRegex({LR"(^< *([+]?[0-9]+) *sc *>)"}, 0, L""), LifeTimeType::Scope }
} };

LifeTime::LifeTime(LifeTimeType lifetimeType, double value)
	: Token(Token::LifeTime, lifetimeType)
	, lifetimeValue(value) {
}

std::wstring LifeTime::str() const {
	std::wstringstream ret;
	switch (valueType) {
	case LifeTimeType::Line:
		ret << L'<' << static_cast<int>(lifetimeValue) << L'>';
		break;
	case LifeTimeType::Second:
		ret << L'<' << lifetimeValue << L"s>";
		break;
	case LifeTimeType::Scope:
		ret << L'<' << static_cast<int>(lifetimeValue) << L"sc>";
		break;
	}
	return ret.str();
}

std::unique_ptr<Token> LifeTime::getToken(std::wstring::const_iterator& start, std::wstring::const_iterator& end, Token* previousToken) {
	std::wsmatch match;
	for (const auto& [regex, tokenType] : regexTokenList) {
		if (std::regex_search(start, end, match, regex)) {
			start = match.suffix().first;
			return std::make_unique<LifeTime>(tokenType, std::stod(match[2]));
		}
	}
	return nullptr;
}
