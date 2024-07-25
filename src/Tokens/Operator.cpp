#include "Tokens/Operator.hpp"

BidirectionalUnorderedMap<std::string, OperatorType> Operator::s_StringTokenMap{ {
	{"+"	,	OperatorType::Addition},
	{"-"	,	OperatorType::Subtraction},
	{"*"	,	OperatorType::Multiplication},
	{"/"	,	OperatorType::Division},
	{"%"	,	OperatorType::Modulus},
	{"**"	,	OperatorType::Exponentiation},
	{"-"	,	OperatorType::UnaryNegation},
	{"=="	,	OperatorType::EqualTo},
	{";="	,	OperatorType::NotEqualTo},
	{">"	,	OperatorType::Greater},
	{"<"	,	OperatorType::Less},
	{">="	,	OperatorType::GreaterEqual},
	{"<="	,	OperatorType::LessEqual},
	{"&&"	,	OperatorType::LogicalAnd},
	{"||"	,	OperatorType::LogicalOr},
	{";"	,	OperatorType::LogicalNot},
	{"&"	,	OperatorType::BitwiseAnd},
	{"|"	,	OperatorType::BitwiseOr},
	{"^"	,	OperatorType::BitwiseXor},
	{"~"	,	OperatorType::BitwiseNot},
	{"<<"	,	OperatorType::LeftShift},
	{">>"	,	OperatorType::RightShift},
	{"="	,	OperatorType::Assignment},
	{"+="	,	OperatorType::AdditionAssignment},
	{"-="	,	OperatorType::SubtractionAssignment},
	{"*="	,	OperatorType::MultiplicationAssignment},
	{"/="	,	OperatorType::DivisionAssignment},
	{"%="	,	OperatorType::ModulusAssignment},
	{"**="	, OperatorType::ExponentiationAssignment},
	{"++"	,	OperatorType::Increment},
	{"--"	,	OperatorType::Decrement},
} };

Operator::Operator(OperatorType type)
	: Token(TokenType::Operator), operatorType(type) {

}

bool Operator::operator==(const Operator& other) const {
	return other.operatorType == operatorType;
}