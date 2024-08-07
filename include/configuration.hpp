#pragma once
#include "Token.hpp"
#include "Tokens/LifeTime.hpp"
#include "Tokens/Operator.hpp"

enum class VariableDeclType {
	VarVarVar,
	VarVarConst,
	VarConstVar,
	VarConstConst,
	ConstVarVar,
	ConstVarConst,
	ConstConstVar,
	ConstConstConst,

	Void
};
enum class IdentifierDeclType {
	Variable,
	Function,
	Type
};
struct VariableLifeTime {
	enum LifeTimeType {
		Line,
		Second,
		Scope
	};
	LifeTimeType type;
	double value;

	VariableLifeTime();
	VariableLifeTime(Token* token);
};
class ASTNode;

struct VariableDeclInfo {
	VariableDeclType variableDeclType;
	std::wstring variableType;
	std::wstring variableName;
	VariableLifeTime lifetime;
	std::unique_ptr<ASTNode> defaultValue;
};

std::wstring getVarDeclTypeString(VariableDeclType type);
std::wstring getVarLifetimeString(VariableLifeTime::LifeTimeType type);
std::wstring getOperatorString(int type);