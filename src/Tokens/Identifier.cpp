#include "Tokens/Identifier.hpp"

std::wregex Identifier::s_regex = Identifier::compileRegex();

Identifier::Identifier(const std::wstring& string)
	: Token(Token::Identifier)
	, identifierName(string) {

}

std::wstring Identifier::str() const {
	return identifierName;
}

std::unique_ptr<Token> Identifier::getToken(std::wstring::const_iterator& start, std::wstring::const_iterator& end, Token* previousToken) {
	std::wsmatch match;
	if (std::regex_search(start, end, match, s_regex)) {
		start = match.suffix().first;
		return std::make_unique<Identifier>(match[0]);
	}
	return nullptr;
}

std::wregex Identifier::compileRegex() {
	return generateRegex({ LR"([a-zA-Z]([a-zA-Z0-9_]*))" }, 0) ;
}
