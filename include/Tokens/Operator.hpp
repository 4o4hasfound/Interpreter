#pragma once
#include <set>
#include <regex>
#include <memory>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string_view>
#include <unordered_map>

#include "Token.hpp"
#include "GenerateRegex.hpp"
#include "Container/BidirectionalUnorderedMap.hpp"

class Operator : public Token {
public:
	enum OperatorType {
		Addition,
		Subtraction,
		Multiplication,
		Division,
		Modulus,
		Exponentiation,
		UnaryNegation,
		UnaryPlus,
		UnaryAbs,
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
		LeftShiftAssignment,
		RightShiftAssignment,
		Assignment,
		AdditionAssignment,
		SubtractionAssignment,
		MultiplicationAssignment,
		DivisionAssignment,
		ModulusAssignment,
		ExponentiationAssignment,
		BitwiseAndAssignment,
		BitwiseOrAssignment,
		BitwiseXorAssignment,
		BitwiseNotAssignment,
		LogicalAndAssignment,
		LogicalOrAssignment,
		LogicalNotAssignment,
		FrontIncrement,
		EndIncrement,
		FrontDecrement,
		EndDecrement,
	};
public:
	Operator(OperatorType type);

	virtual std::wstring str() const override;

	static std::unique_ptr<Token> getToken(std::wstring::const_iterator& start, std::wstring::const_iterator& end, Token *previousToken);
	static BidirectionalUnorderedMap<std::wstring, OperatorType> stringTokenMap;

private:
	static std::wregex s_regex;
	
	static std::wregex compileRegex();
};