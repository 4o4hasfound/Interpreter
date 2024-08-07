#include "Lexer.hpp"

Lexer::Lexer(std::vector<std::unique_ptr<Token>>& tokens)
	: m_tokens(tokens) {

}

void Lexer::tokenize(const std::wstring& input) {
	std::wstring str = std::regex_replace(input, std::wregex(LR"(\t)"), L"    ");
	str = std::regex_replace(input, std::wregex(LR"((\n)+)"), L"\t");
	std::wstring::const_iterator start = str.cbegin(), end = str.cend();
	Token* lastToken = nullptr;
	while (start != end) {
		WhiteSpace::eat(start, end);
		std::unique_ptr<Token> ptr = nullptr;

		if ((ptr = StatementTerminator::getToken(start, end, lastToken))) {
			m_tokens.push_back(std::move(ptr));
		}
		else if ((ptr = StringLiteral::getToken(start, end, lastToken))) {
			m_tokens.push_back(std::move(ptr));
		}
		else if ((ptr = NumericLiteral::getToken(start, end, lastToken))) {
			m_tokens.push_back(std::move(ptr));
		}
		else if ((ptr = Boolean::getToken(start, end, lastToken))) {
			m_tokens.push_back(std::move(ptr));
		}
		else if ((ptr = LifeTime::getToken(start, end, lastToken))) {
			m_tokens.push_back(std::move(ptr));
		}
		else if ((ptr = Operator::getToken(start, end, lastToken))) {
			m_tokens.push_back(std::move(ptr));
		}
		else if ((ptr = Delimiter::getToken(start, end, lastToken))) {
			m_tokens.push_back(std::move(ptr));
		}
		else if ((ptr = BuiltInKeyword::getToken(start, end, lastToken))) {
			m_tokens.push_back(std::move(ptr));
		}
		else if ((ptr = Identifier::getToken(start, end, lastToken))) {
			m_tokens.push_back(std::move(ptr));
		}
		lastToken = m_tokens.back().get();
	}
}