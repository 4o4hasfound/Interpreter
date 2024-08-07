#include "Tokens/NumericLiteral.hpp"

std::vector<std::pair<std::wregex, NumericLiteral::NumericLiteralType>> NumericLiteral::regexTokenList{ {
	{generateRegex({LR"(([-+]?[0-9]+\.[0-9]*))"}, 0, L"a-zA-Z"), NumericLiteralType::Float},
	{generateRegex({LR"(([-+]?[0-9]+))"}, 0, L"a-zA-Z"), NumericLiteralType::Interger}
} };

NumericLiteral::NumericLiteral(NumericLiteralType literalType, double value)
	: Token(TokenType::NumericLiteral, literalType)
	, literalValue(value) {

}

std::wstring NumericLiteral::str() const {
	switch (valueType) {
	case NumericLiteral::Interger:
		return std::to_wstring(static_cast<std::int64_t>(literalValue));
	case NumericLiteral::Float:
		return std::to_wstring(static_cast<double>(literalValue));
	}
	return L"";
}

std::unique_ptr<Token> NumericLiteral::getToken(std::wstring::const_iterator& start, std::wstring::const_iterator& end, Token* previousToken) {
	std::wsmatch match;
	for (const auto& [regex, tokenType] : regexTokenList) {
		if (std::regex_search(start, end, match, regex)) {
			if (match[0].str()[0] == L'-' || match[0].str()[0] == L'+') {
				if (previousToken->isType(Token::Identifier)
					|| previousToken->isType(Token::Delimiter, Delimiter::RParen)
					|| previousToken->isType(Token::NumericLiteral)
					|| previousToken->isType(Token::StringLiteral)
					|| previousToken->isType(Token::Operator, Operator::UnaryAbs)
					|| previousToken->isType(Token::Operator, Operator::UnaryPlus)
					|| previousToken->isType(Token::Operator, Operator::UnaryNegation)) {
					return nullptr;
				}
			}
			start = match.suffix().first;
			return std::make_unique<NumericLiteral>(tokenType, std::stod(match[0]));
		}
	}
	return nullptr;
}