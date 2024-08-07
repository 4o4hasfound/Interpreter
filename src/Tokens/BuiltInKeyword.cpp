#include "Tokens/BuiltInKeyword.hpp"

BidirectionalUnorderedMap<std::wstring, BuiltInKeyword::KeywordType> BuiltInKeyword::stringTokenMap{ {
	{L"var", BuiltInKeyword::VarVarVar},
	{L"var var", BuiltInKeyword::VarVarVar},
	{L"var const", BuiltInKeyword::VarConstConst},
	{L"var var var", BuiltInKeyword::VarVarVar},
	{L"var var const", BuiltInKeyword::VarVarConst},
	{L"var const var", BuiltInKeyword::VarConstVar},
	{L"var const const", BuiltInKeyword::VarConstConst},
	{L"const", BuiltInKeyword::ConstConstConst},
	{L"const var", BuiltInKeyword::ConstVarVar},
	{L"const const", BuiltInKeyword::ConstConstConst},
	{L"const var var", BuiltInKeyword::ConstVarVar},
	{L"const var const", BuiltInKeyword::ConstVarConst},
	{L"const const var", BuiltInKeyword::ConstConstVar},
	{L"const const const", BuiltInKeyword::ConstConstConst},
	{L"if", BuiltInKeyword::If},
	{L"else", BuiltInKeyword::Else},
	{L"ima dip", BuiltInKeyword::Return},
	{L"function", BuiltInKeyword::Function},
	{L"print", BuiltInKeyword::True},
	{L"previous", BuiltInKeyword::Previous},
	{L"current", BuiltInKeyword::Current},
	{L"reverse", BuiltInKeyword::Reverse},
	{L"noop", BuiltInKeyword::Noop}
} };
std::vector<std::wstring> BuiltInKeyword::keywordRegexes{
	LR"((var|const)( (var|const)){0,2})",
	L"if",
	L"else",
	L"ima dip",
	L"(?=[function]{2,})(f?u?n?c?t?i?o?n?)",
	L"true",
	L"false",
	L"maybe",
	L"print",
	L"previous",
	L"current",
	L"reverse",
	L"noop"
};
std::wregex BuiltInKeyword::s_regex = BuiltInKeyword::compileRegex();
std::wregex BuiltInKeyword::s_functionRegex = generateRegex({LR"((?=[function]{2,})(f?u?n?c?t?i?o?n?)$)"}, 0);

BuiltInKeyword::BuiltInKeyword(KeywordType keywordType)
	: Token(Token::BuiltInKeyWord, keywordType) {

}

std::wstring BuiltInKeyword::str() const {
	return stringTokenMap[static_cast<KeywordType>(valueType)];
}

std::unique_ptr<Token> BuiltInKeyword::getToken(std::wstring::const_iterator& start, std::wstring::const_iterator& end, Token* previousToken) {
	std::wsmatch match;
	if (std::regex_search(start, end, match, s_regex)) {
		start = match.suffix().first;
		if (std::regex_match(match[0].str(), s_functionRegex)) {
			return std::make_unique<BuiltInKeyword>(KeywordType::Function);
		}
		return std::make_unique<BuiltInKeyword>(stringTokenMap[match[0]]);
	}
	return nullptr;
}

std::wregex BuiltInKeyword::compileRegex() {
	return generateRegex(keywordRegexes, 0, LR"(a-zA-Z0-9_)");
}
