#pragma once
#include <vector>
#include <memory>
#include <string>

#include "configuration.hpp"
#include "Tokens/StringLiteral.hpp"
#include "Tokens/NumericLiteral.hpp"
#include "Tokens/Identifier.hpp"
#include "Tokens/Operator.hpp"
#include "Tokens/Boolean.hpp"

class ASTNode {
public:
	enum NodeType {
		Program,
		Block,
		VariableDeclaration,
		FunctionDeclaration,
		//ClassDeclaration,
		Expression,
		NormalStatement,
		DebugStatement,
		IfStatement,
		ReturnStatement,
		BreakStatement,
		//ContinueStatement,
		ReverseStatement,
		BinaryExpression,
		UnaryExpression,
		StringLiteralNode,
		IntergerLiteralNode,
		FloatLiteral,
		Boolean,
		IdentifierNode,
		AssignmentExpression,
		CallExpression,
		//MemberExpression,
		//ArrayExpression,
		//IndexExpression
	};
	ASTNode(NodeType type);
	virtual ~ASTNode() {};
	NodeType nodeType;
};

class Program: public ASTNode {
public:
	Program();

	std::vector<std::unique_ptr<ASTNode>> nodes;
};
class Block : public ASTNode {
public:
	Block();

	std::vector<std::unique_ptr<ASTNode>> nodes;
};
class VariableDeclaration : public ASTNode {
public:
	VariableDeclaration();

	VariableDeclType variableDeclType;
	std::wstring variableType;
	int priority;
	std::vector<VariableDeclInfo> declarations;
};
class FunctionDeclaration : public ASTNode {
public:
	FunctionDeclaration();

	std::wstring identifierName;
	VariableDeclType returnVarDeclType;
	std::wstring returnVarType;
	std::vector<VariableDeclInfo> parameters;
	std::unique_ptr<ASTNode> block;
};
class Expression : public ASTNode {
public:
	Expression();

	std::unique_ptr<ASTNode> expression;
};
class Statement : public ASTNode {
public:
	Statement(NodeType type);

	std::unique_ptr<ASTNode> statement;
};
class NormalStatement : public Statement {
public:
	NormalStatement();
};
class DebugStatement : public Statement {
public:
	DebugStatement();
};
class IfStatement : public ASTNode {
public:
	IfStatement();

	std::unique_ptr<ASTNode> condition;
	std::unique_ptr<ASTNode> body;
}; 
class ReturnStatement : public ASTNode{
public:
	ReturnStatement();

	std::unique_ptr<ASTNode> expression;
};
class ReverseStatement : public ASTNode {
public:
	ReverseStatement();
};
class BinaryExpression : public ASTNode {
public:
	BinaryExpression();
	BinaryExpression(Operator::OperatorType opType);

	std::unique_ptr<ASTNode> LExpression;
	Operator::OperatorType operatorType;
	std::unique_ptr<ASTNode> RExpression;
};
class UnaryExpression : public ASTNode {
public:
	UnaryExpression();
	UnaryExpression(Operator::OperatorType opType);

	std::unique_ptr<ASTNode> expression;
	Operator::OperatorType operatorType;
};
class StringLiteralNode : public ASTNode {
public:
	StringLiteralNode(Token* token);

	std::wstring value;
};
class IntergerLiteralNode : public ASTNode {
public:
	IntergerLiteralNode(Token* token);

	std::int64_t value;
};
class FloatLiteralNode : public ASTNode {
public:
	FloatLiteralNode(Token* token);

	double value;
};
class BooleanNode : public ASTNode {
public:
	BooleanNode(Boolean::BooleanType type);
	BooleanNode(Token* token);

	Boolean::BooleanType booleanType;
};
class IdentifierNode : public ASTNode {
public:
	IdentifierNode(Token* token);

	std::wstring identifierName;
};
class AssignmentExpression : public BinaryExpression {
public:
	AssignmentExpression();
};
class CallExpression : public ASTNode {
public:
	CallExpression();

	std::unique_ptr<ASTNode> identifier;
	std::vector<std::unique_ptr<ASTNode>> arguments;
};