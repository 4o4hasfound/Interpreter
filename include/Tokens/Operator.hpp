#pragma once
#include <set>
#include <string_view>
#include <unordered_map>

#include "Token.hpp"
#include "Container/BidirectionalUnorderedMap.hpp"

enum class OperatorType {
	Addition,
	Subtraction,
	Multiplication,
	Division,
	Modulus,
	Exponentiation,
	UnaryNegation,
	EqualTo,
	NotEqualTo,
	Greater,
	Less,
	GreaterEqual,
	LessEqual,
	LogicalAnd,
	LogicalOr,
	LogicalNot,
	BitwiseAnd,
	BitwiseOr,
	BitwiseXor,
	BitwiseNot,
	LeftShift,
	RightShift,
	Assignment,
	AdditionAssignment,
	SubtractionAssignment,
	MultiplicationAssignment,
	DivisionAssignment,
	ModulusAssignment,
	ExponentiationAssignment,
	Increment,
	Decrement,
};

class Operator : public Token {
public:
	Operator(OperatorType type);
	bool operator==(const Operator& other) const;

	OperatorType operatorType;

	static Token* getToken(std::string_view string);
	static BidirectionalUnorderedMap<std::string, OperatorType> s_StringTokenMap;
	static std::multiset<int, Operator> s_StringTokenMap;
};