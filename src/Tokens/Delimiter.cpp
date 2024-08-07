#include "Tokens/Delimiter.hpp"

BidirectionalUnorderedMap<std::wstring, Delimiter::DelimiterType> Delimiter::stringTokenMap{ {
	{L"(", Delimiter::LParen},
	{L")", Delimiter::RParen},
	{L"[", Delimiter::LBracket},
	{L"]", Delimiter::RBracket},
	{L"{", Delimiter::LCurlyBracket},
	{L"}", Delimiter::RCurlyBracket},
	{L",", Delimiter::Comma},
} };
std::wregex Delimiter::s_regex = Delimiter::compileRegex();

Delimiter::Delimiter(DelimiterType delimiterType) 
	: Token(Token::Delimiter, delimiterType) {

}

std::wstring Delimiter::str() const {
	return stringTokenMap[static_cast<DelimiterType>(valueType)];
}

std::unique_ptr<Token> Delimiter::getToken(std::wstring::const_iterator& start, std::wstring::const_iterator& end, Token* previousToken) {
	std::wsmatch match;
	if (std::regex_search(start, end, match, s_regex)) {
		start = match.suffix().first;
		return std::make_unique<Delimiter>(stringTokenMap[match[0]]);
	}
	return nullptr;
}

std::wregex Delimiter::compileRegex() {
	std::vector<std::wstring> list = stringTokenMap.listA();

	return generateRegex(list, 1);
}
