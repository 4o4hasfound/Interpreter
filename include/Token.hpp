#pragma once
#include <any>
#include <string>
#include <type_traits>

// Template helper class that detect if a class has certain member variable
namespace {
	template <typename T, typename = int>
	struct HasValueType : std::false_type { };

	template <typename T>
	struct HasValueType <T, decltype((void)T::valueType, 0)> : std::true_type { };
}

struct Token {
	enum TokenType {
		NumericLiteral,
		StringLiteral,
		Boolean,
		Operator,
		Delimiter,
		StatementTerminator,
		Identifier,
		BuiltInKeyWord,
		LifeTime
	};

	TokenType type;
	int valueType;

	Token(TokenType tokenType, int underLyingValueType = -1);

	bool isType(TokenType targetTokenType) const;
	bool isType(TokenType targetTokenType, int targetValueType) const;

	virtual std::wstring str() const = 0;
};