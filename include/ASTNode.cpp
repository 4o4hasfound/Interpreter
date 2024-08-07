#include "ASTNodes/ASTNode.hpp"

ASTNode::ASTNode(NodeType type)
	: nodeType(type) {

}

Program::Program()
	: ASTNode(ASTNode::Program) {

}

Block::Block()
	: ASTNode(ASTNode::Block) {

}


VariableDeclaration::VariableDeclaration()
	: ASTNode(ASTNode::VariableDeclaration) {

}

FunctionDeclaration::FunctionDeclaration()
	: ASTNode(ASTNode::FunctionDeclaration) {

}

Expression::Expression()
	: ASTNode(ASTNode::Expression) {

}

Statement::Statement(NodeType type)
	: ASTNode(type) {

}

NormalStatement::NormalStatement()
	: Statement(ASTNode::NormalStatement) {

}

DebugStatement::DebugStatement()
	: Statement(ASTNode::DebugStatement) {

}

IfStatement::IfStatement()
	: ASTNode(ASTNode::IfStatement) {

}


ReturnStatement::ReturnStatement()
	: ASTNode(ASTNode::ReturnStatement) {

}

ReverseStatement::ReverseStatement()
	: ASTNode(ASTNode::ReverseStatement) {

}

BinaryExpression::BinaryExpression()
	: ASTNode(ASTNode::BinaryExpression) {

}

BinaryExpression::BinaryExpression(Operator::OperatorType opType)
	: ASTNode(ASTNode::BinaryExpression)
	, operatorType(opType) {

}

UnaryExpression::UnaryExpression()
	: ASTNode(ASTNode::UnaryExpression) {

}

UnaryExpression::UnaryExpression(Operator::OperatorType opType)
	: ASTNode(ASTNode::BinaryExpression)
	, operatorType(opType) {

}

StringLiteralNode::StringLiteralNode(Token* token)
	: ASTNode(ASTNode::StringLiteralNode)
	, value(token->str()){

}


IntergerLiteralNode::IntergerLiteralNode(Token* token)
	: ASTNode(ASTNode::IntergerLiteralNode)
	, value(dynamic_cast<NumericLiteral*>(token)->literalValue) {

}


FloatLiteralNode::FloatLiteralNode(Token* token)
	: ASTNode(ASTNode::FloatLiteral)
	, value(dynamic_cast<NumericLiteral*>(token)->literalValue) {

}


IdentifierNode::IdentifierNode(Token* token)
	: ASTNode(ASTNode::IdentifierNode)
	, identifierName(token->str()) {

}


AssignmentExpression::AssignmentExpression() {

}

CallExpression::CallExpression()
	: ASTNode(ASTNode::CallExpression) {

}

BooleanNode::BooleanNode(Boolean::BooleanType type)
	: ASTNode(ASTNode::Boolean),
	booleanType(type) {
}
BooleanNode::BooleanNode(Token* token)
	: ASTNode(ASTNode::Boolean),
	booleanType(static_cast<Boolean::BooleanType>(token->valueType)) {
}
