#pragma once
#include <vector>
#include <memory>

#include "Token.hpp"
#include "ASTNodes/ASTNode.hpp"

#include "Tokens/LifeTime.hpp"
#include "Tokens/Operator.hpp"
#include "Tokens/Delimiter.hpp"
#include "Tokens/WhiteSpace.hpp"
#include "Tokens/Identifier.hpp"
#include "Tokens/StringLiteral.hpp"
#include "Tokens/StringLiteral.hpp"
#include "Tokens/NumericLiteral.hpp"
#include "Tokens/BuiltInKeyword.hpp"
#include "Tokens/StatementTerminator.hpp"

class AST {
public:
	AST(const std::vector<std::unique_ptr<Token>>& tokens);

	void build();
	void debug(ASTNode* node, int depth = 0) const;
	void debug(const VariableDeclInfo& declInfo, int depth = 0) const;
private:
	std::unique_ptr<Program> m_program;
	std::unique_ptr<Statement> functionNode;
	std::unique_ptr<Statement> variableNode;
	
	int m_index, m_fallbackIndex;
	const std::vector<std::unique_ptr<Token>>& m_tokens;
	
	Token* peek(int delta = 0) const;
	bool match(Token::TokenType type) const;
	bool match(Token::TokenType type, int valueType) const;
	void loadIndex();
	void fallback();
	Token* advance(int delta = 1);
	Token* previous() const;
	Token* consume(Token::TokenType type, const std::string& errorMessage);
	Token* consume(Token::TokenType type, int valueType, const std::string& errorMessage);
	bool isEnd() const;

	std::unique_ptr<Program> parseProgram();
	std::unique_ptr<ASTNode> parseBlock(bool checkForStatementType = 1);
	std::unique_ptr<ASTNode> parseType();
	std::unique_ptr<Statement> parseFunctionDeclaration();
	std::unique_ptr<Statement> parseVariableDeclaration();
	std::unique_ptr<ASTNode> parseUnary();
	std::unique_ptr<ASTNode> parsePrimary();
	std::unique_ptr<ASTNode> parseExpression(int precedence = 0);
	std::unique_ptr<ASTNode> parseExpressionStatement();
	std::unique_ptr<Statement> parseIfStatement();
	std::unique_ptr<Statement> parseReverseStatement();
	std::unique_ptr<Statement> parseReturnStatement();
	std::unique_ptr<Statement> parseStatementType();
	void skipStatementTerminator();

	VariableDeclType parseDeclType();
	Token* parseIdentifier();
	VariableLifeTime parseLifeTime();

	VariableDeclType getVariableDeclType(Token* token) const;
	int getPrecendence(Token* token) const;
	bool isAssignmentOperator(Token* token) const;
	bool isUnaryOperator(Token* token) const;
	bool isPrefixUnaryOperator(Token* token) const;
	bool isPostfixUnaryOperator(Token* token) const;

	bool tokenIsType(Token* token, Token::TokenType type) const;
	bool tokenIsType(Token* token, Token::TokenType type, int valueType) const;

	static const std::unordered_map<Operator::OperatorType, int> s_presedence;
};