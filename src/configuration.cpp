#include "configuration.hpp"

VariableLifeTime::VariableLifeTime()
	: type(Scope), value(1) {
}

VariableLifeTime::VariableLifeTime(Token* token)
	: type(static_cast<LifeTimeType>(token->valueType))
	, value(dynamic_cast<LifeTime*>(token)->lifetimeValue) {

}

std::wstring getVarDeclTypeString(VariableDeclType type) {
	switch (type) {
	case VariableDeclType::VarVarVar:
		return L"var var var";
	case VariableDeclType::VarVarConst:
		return L"var var const";
	case VariableDeclType::VarConstVar:
		return L"var const var";
	case VariableDeclType::VarConstConst:
		return L"var const const";
	case VariableDeclType::ConstVarVar:
		return L"const var var";
	case VariableDeclType::ConstVarConst:
		return L"const var const";
	case VariableDeclType::ConstConstVar:
		return L"const const var";
	case VariableDeclType::ConstConstConst:
		return L"const const const";
	}
}

std::wstring getVarLifetimeString(VariableLifeTime::LifeTimeType type) {
	switch (type) {
	case VariableLifeTime::Line:
		return L"lines";
	case VariableLifeTime::Scope:
		return L"scopes";
	case VariableLifeTime::Second:
		return L"seconds";
	}
}

std::wstring getOperatorString(int type) {
	return Operator::stringTokenMap[static_cast<Operator::OperatorType>(type)];
}