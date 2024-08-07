#include "Tokens/Operator.hpp"

BidirectionalUnorderedMap<std::wstring, Operator::OperatorType> Operator::stringTokenMap{ {
	{L"[[positive]]"	,	OperatorType::UnaryPlus},
	{L"[[negative]]"	,	OperatorType::UnaryNegation},
	{L"[[absolute]]"	,	OperatorType::UnaryAbs},
	{L"**="	,	OperatorType::ExponentiationAssignment},
	{L"**="	,	OperatorType::ExponentiationAssignment},
	{L"+++"	,	OperatorType::FrontIncrement},
	{L"++"	,	OperatorType::EndIncrement},
	{L"---"	,	OperatorType::FrontDecrement},
	{L"--"	,	OperatorType::EndDecrement},
	{L"<<="	,	OperatorType::LeftShiftAssignment},
	{L">>="	,	OperatorType::RightShiftAssignment},
	{L";=="	,	OperatorType::NotEqualTo},
	{L";=="	,	OperatorType::LogicalNotAssignment},
	{L"&&="	,	OperatorType::LogicalAndAssignment},
	{L"||="	,	OperatorType::LogicalOrAssignment},
	{L"**"	,	OperatorType::Exponentiation},
	{L"=="	,	OperatorType::EqualTo},
	{L">="	,	OperatorType::GreaterEqual},
	{L"<="	,	OperatorType::LessEqual},
	{L"&&"	,	OperatorType::LogicalAnd},
	{L"||"	,	OperatorType::LogicalOr},
	{L"<<"	,	OperatorType::LeftShift},
	{L">>"	,	OperatorType::RightShift},
	{L"+="	,	OperatorType::AdditionAssignment},
	{L"-="	,	OperatorType::SubtractionAssignment},
	{L"*="	,	OperatorType::MultiplicationAssignment},
	{L"/="	,	OperatorType::DivisionAssignment},
	{L"%="	,	OperatorType::ModulusAssignment},
	{L"&="	,	OperatorType::BitwiseAndAssignment},
	{L"|="	,	OperatorType::BitwiseOrAssignment},
	{L"^="	,	OperatorType::BitwiseXorAssignment},
	{L"~="	,	OperatorType::BitwiseNotAssignment},
	{L"="	,	OperatorType::Assignment},
	{L"+"	,	OperatorType::Addition},
	{L"-"	,	OperatorType::Subtraction},
	{L"*"	,	OperatorType::Multiplication},
	{L"/"	,	OperatorType::Division},
	{L"%"	,	OperatorType::Modulus},
	{L";"	,	OperatorType::LogicalNot},
	{L"&"	,	OperatorType::BitwiseAnd},
	{L"|"	,	OperatorType::BitwiseOr},
	{L"^"	,	OperatorType::BitwiseXor},
	{L"~"	,	OperatorType::BitwiseNot},
	{L">"	,	OperatorType::Greater},
	{L"<"	,	OperatorType::Less},
} };

std::wregex Operator::s_regex = Operator::compileRegex();

Operator::Operator(OperatorType type)
	: Token(TokenType::Operator, type) {

}

std::wstring Operator::str() const {
	return stringTokenMap[static_cast<OperatorType>(valueType)];
}

std::unique_ptr<Token> Operator::getToken(std::wstring::const_iterator& start, std::wstring::const_iterator& end, Token* previousToken) {
	std::wsmatch match;
	if (std::regex_search(start, end, match, s_regex)) {
		start = match.suffix().first;
		return std::make_unique<Operator>(stringTokenMap[match[0]]);
	}
	return nullptr;
}

std::wregex Operator::compileRegex() {
	std::vector<std::wstring> list = stringTokenMap.listA();

	//// Sort it to make the longer operators get processed first
	//std::sort(list.begin(), list.end(), [](const std::wstring& a, const std::wstring& b) {
	//	return a.size() > b.size();
	//	});

	return generateRegex(list, 1);
}
