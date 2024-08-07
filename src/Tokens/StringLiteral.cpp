#include "Tokens/StringLiteral.hpp"

std::wregex StringLiteral::s_regex(LR"(^("+)(.*)\1)", std::regex_constants::optimize);

StringLiteral::StringLiteral(const std::wstring& value)
	: Token(TokenType::StringLiteral)
	, literalValue(value) {

}

std::wstring StringLiteral::str() const {
	return literalValue;
}

std::unique_ptr<Token> StringLiteral::getToken(std::wstring::const_iterator& start, std::wstring::const_iterator& end, Token* previousToken) {
	std::wsmatch match;
	if (std::regex_search(start, end, match, s_regex)) {
		start = match.suffix().first;
		if (match.size() > 2) {
			return std::make_unique<StringLiteral>(match[2]);
		}
		else {
			return std::make_unique<StringLiteral>(L"");
		}
	}
	return nullptr;
}
