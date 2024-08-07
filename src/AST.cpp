#include "AST.hpp"
// Abstract syntax tree

const std::unordered_map<Operator::OperatorType, int> AST::s_presedence{ {
	{Operator::LogicalNot, 15},
	{Operator::BitwiseNot, 15},
	{Operator::LogicalNot, 15},
	{Operator::BitwiseNot, 15},
	{Operator::UnaryPlus, 15},
	{Operator::UnaryNegation, 15},
	{Operator::FrontIncrement, 15},
	{Operator::FrontDecrement, 15},
	{Operator::EndIncrement, 15},
	{Operator::EndDecrement, 15},
	{Operator::Exponentiation, 14},
	{Operator::Multiplication, 13},
	{Operator::Division, 13},
	{Operator::Modulus, 13},
	{Operator::Addition, 12},
	{Operator::Subtraction, 12},
	{Operator::LeftShift, 11},
	{Operator::RightShift, 11},
	{Operator::Less, 10},
	{Operator::LessEqual, 10},
	{Operator::Greater, 10},
	{Operator::GreaterEqual, 10},
	{Operator::EqualTo, 9},
	{Operator::NotEqualTo, 9},
	{Operator::BitwiseAnd, 8},
	{Operator::BitwiseXor, 7},
	{Operator::BitwiseOr, 6},
	{Operator::LogicalAnd, 5},
	{Operator::LogicalOr, 4},
	{Operator::Assignment, 2},
	{Operator::AdditionAssignment, 2},
	{Operator::SubtractionAssignment, 2},
	{Operator::MultiplicationAssignment, 2},
	{Operator::DivisionAssignment, 2},
	{Operator::ModulusAssignment, 2},
	{Operator::ExponentiationAssignment, 2},
	{Operator::BitwiseAndAssignment, 2},
	{Operator::BitwiseOrAssignment, 2},
	{Operator::BitwiseXorAssignment, 2},
	{Operator::BitwiseNotAssignment, 2},
	{Operator::LogicalAndAssignment, 2},
	{Operator::LogicalOrAssignment, 2},
	{Operator::LogicalNotAssignment, 2},
	{Operator::LeftShiftAssignment, 2},
	{Operator::RightShiftAssignment, 2},
} };

AST::AST(const std::vector<std::unique_ptr<Token>>& tokens)
	: m_tokens(tokens) {
}

void AST::build() {
	m_program = parseProgram();
	debug(m_program.get());
}

void AST::debug(ASTNode* node, int depth) const {
	if (!node) {
		return;
	}
	for (int i = 0; i < depth; ++i) {
		std::wcout << L"    ";
	}
	if (depth) {
		//std::wcout << L"► ";
	}
	switch (node->nodeType) {
	case ASTNode::Program: {
		Program* program = dynamic_cast<Program*>(node);
		std::wcout << L"Program: "<<program->nodes.size()<<L"\n";
		for (auto& n : program->nodes) {
			debug(n.get(), depth+1);
		}
		break;
	}
	case ASTNode::Block:{
		Block* block = dynamic_cast<Block*>(node);
		std::wcout << L"Block: " << block->nodes.size() << L"\n";
		for (auto& n : block->nodes) {
			debug(n.get(), depth+1);
		}
		break;
	}
	case ASTNode::VariableDeclaration:{
		VariableDeclaration* decl = dynamic_cast<VariableDeclaration*>(node);
		std::wcout << "Variable: " << decl->declarations.size()<<"\n";
		for (auto& n : decl->declarations) {
			debug(n, depth + 1);
		}
		break;
	}
	case ASTNode::FunctionDeclaration:{
		FunctionDeclaration* func = dynamic_cast<FunctionDeclaration*>(node);
		std::wcout << "Function: "<<func->identifierName<<": " << getVarDeclTypeString(func->returnVarDeclType) << " " << func->returnVarType << "\n";
		for (auto& n : func->parameters) {
			debug(n, depth+1);
		}
		debug(func->block.get(), depth+1);
		break;
	}
	case ASTNode::Expression:{
		Expression* expr = dynamic_cast<Expression*>(node);
		std::wcout << "Expression:\n";
		debug(expr->expression.get(), depth+1);
		break;
	}
	case ASTNode::NormalStatement:{
		NormalStatement* statement = dynamic_cast<NormalStatement*>(node);
		std::wcout << "Statement: \n";
		debug(statement->statement.get(), depth + 1);
		break;
	}
	case ASTNode::DebugStatement:{
		DebugStatement* statement = dynamic_cast<DebugStatement*>(node);
		std::wcout << "Debug Statement: \n";
		debug(statement->statement.get(), depth+1);
		break;
	}
	case ASTNode::IfStatement:{
		IfStatement* ifStatement = dynamic_cast<IfStatement*>(node);
		std::wcout << "If Statement: \n";
		debug(ifStatement->condition.get(), depth + 1);
		debug(ifStatement->body.get(), depth + 1);
		break;
	}
	case ASTNode::ReturnStatement:{
		ReturnStatement* retStatement = dynamic_cast<ReturnStatement*>(node);
		std::wcout << "Ima dip Statement: \n";
		debug(retStatement->expression.get(), depth + 1);
		break;
	}
	case ASTNode::ReverseStatement:{
		ReverseStatement* revStatement = dynamic_cast<ReverseStatement*>(node);
		std::wcout << "Reverse Statement: \n";
		break;
	}
	case ASTNode::BinaryExpression:{
		BinaryExpression* biOP = dynamic_cast<BinaryExpression*>(node);
		std::wcout << "Binary Expression Statement: "<<getOperatorString(biOP->operatorType)<<"\n";
		debug(biOP->LExpression.get(), depth+1);
		debug(biOP->RExpression.get(), depth+1);
		break;
	}
	case ASTNode::UnaryExpression:{
		UnaryExpression* uOP = dynamic_cast<UnaryExpression*>(node);
		std::wcout << "Binary Expression Statement: " << getOperatorString(uOP->operatorType) << "\n";
		debug(uOP->expression.get(), depth+1);
		break;
	}
	case ASTNode::StringLiteralNode:{
		StringLiteralNode* literal = dynamic_cast<StringLiteralNode*>(node);
		std::wcout << "String literal: " << literal->value << "\n";
		break;
	}
	case ASTNode::IntergerLiteralNode:{
		IntergerLiteralNode* literal = dynamic_cast<IntergerLiteralNode*>(node);
		std::wcout << "Interger literal: " << literal->value << "\n";
		break;
	}
	case ASTNode::FloatLiteral:{
		FloatLiteralNode* literal = dynamic_cast<FloatLiteralNode*>(node);
		std::wcout << "Float literal: " << literal->value << "\n";
		break;
	}
	case ASTNode::IdentifierNode:{
		IdentifierNode* identifier = dynamic_cast<IdentifierNode*>(node);
		std::wcout << "Identifier: " << identifier->identifierName << "\n";
		break;
	}
	}
}

void AST::debug(const VariableDeclInfo& declInfo, int depth) const {
	for (int i = 0; i < depth; ++i) {
		std::wcout << "    ";
	}
	if (depth) {
		//std::wcout << L"► ";
	}
	std::wcout << "variable:";
	std::wcout << declInfo.variableName << ", "<<getVarDeclTypeString(declInfo.variableDeclType);
	std::wcout << ", " << declInfo.variableType << ", lifetime: "<<declInfo.lifetime.value<<getVarLifetimeString(declInfo.lifetime.type);
	std::wcout << "\n";
	debug(declInfo.defaultValue.get(), depth + 1);
}

Token* AST::peek(int delta) const {
	if (m_index + delta < m_tokens.size()) {
		return m_tokens[m_index + delta].get();
	}
	return nullptr;
}

bool AST::match(Token::TokenType type) const {
	return tokenIsType(peek(), type);
}

bool AST::match(Token::TokenType type, int valueType) const {
	return tokenIsType(peek(), type, valueType);
}

void AST::loadIndex() {
	m_fallbackIndex = m_index;
}

void AST::fallback() {
	m_index = m_fallbackIndex;
}

Token* AST::advance(int delta) {
	Token* ret = peek();
	m_index += delta;
	return ret;
}

Token* AST::previous() const {
	if (m_index - 1 >= 0) {
		return m_tokens[m_index].get();
	}
	return nullptr;
}

Token* AST::consume(Token::TokenType type, const std::string& errorMessage) {
	if (peek()->isType(type)) return advance();
	throw std::runtime_error(errorMessage);
}

Token* AST::consume(Token::TokenType type, int valueType, const std::string& errorMessage) {
	if (peek()->isType(type, valueType)) return advance();
	throw std::runtime_error(errorMessage);
}

bool AST::isEnd() const {
	return m_index >= m_tokens.size();
}

std::unique_ptr<Program> AST::parseProgram() {
	auto program = std::make_unique<Program>();
	while (true) {
		std::unique_ptr<ASTNode> node;
		if ((node = parseIfStatement())
			|| (node = parseReturnStatement())
			|| (node = parseReverseStatement())
			|| (node = parseVariableDeclaration())
			|| (node = parseFunctionDeclaration())
			|| (node = parseIfStatement())
			|| (node = parseExpressionStatement())
			|| (node = parseBlock())) {
			program->nodes.push_back(std::move(node));
		}
		else {
			break;
		}
	}
	return program;
}

std::unique_ptr<ASTNode> AST::parseBlock(bool checkForStatementType) {
	loadIndex();

	if (!tokenIsType(advance(), Token::Delimiter, Delimiter::LCurlyBracket)) {
		fallback();
		return nullptr;
	}

	auto block = std::make_unique<Block>();

	while (true) {
		std::unique_ptr<ASTNode> node;
		if ((node = parseIfStatement())
			|| (node = parseReturnStatement())
			|| (node = parseReverseStatement())
			|| (node = parseVariableDeclaration())
			|| (node = parseFunctionDeclaration())
			|| (node = parseIfStatement())
			|| (node = parseExpressionStatement())
			|| (node = parseBlock())) {
			block->nodes.push_back(std::move(node));
		}
		else {
			if (match(Token::Delimiter, Delimiter::RCurlyBracket)) {
				advance();
				break;
			}
		}
	}
	
	if (checkForStatementType) {
		auto statement = parseStatementType();
		statement->statement = std::move(block);
		return statement;
	}
	else {
		return block;
	}
}

std::unique_ptr<ASTNode> AST::parseType() {
	return std::unique_ptr<ASTNode>();
}

VariableDeclType AST::parseDeclType() {
	Token* declType = peek();
	if (!declType || declType->type != Token::BuiltInKeyWord 
		|| declType->valueType != BuiltInKeyword::VarVarVar
		&& declType->valueType != BuiltInKeyword::VarVarConst
		&& declType->valueType != BuiltInKeyword::VarConstVar
		&& declType->valueType != BuiltInKeyword::VarConstConst
		&& declType->valueType != BuiltInKeyword::ConstVarVar
		&& declType->valueType != BuiltInKeyword::ConstVarConst
		&& declType->valueType != BuiltInKeyword::ConstConstVar
		&& declType->valueType != BuiltInKeyword::ConstConstConst) {
		return VariableDeclType::Void;
	}
	advance();
	return getVariableDeclType(declType);
}

Token* AST::parseIdentifier() {
	Token* identifier = peek();
	if (!tokenIsType(identifier, Token::Identifier)) {
		return nullptr;
	}
	advance();
	return identifier;
}

VariableLifeTime AST::parseLifeTime() {
	Token* lifetime = peek();
	if (!lifetime->isType(Token::LifeTime)) {
		return VariableLifeTime();
	}
	advance();
	return VariableLifeTime(lifetime);
}

std::unique_ptr<Statement> AST::parseFunctionDeclaration() {
	// function id(declType typeId id<lifetime> (=exp), ...) retDeclType retType{}
	loadIndex();

	if (!tokenIsType(advance(), Token::BuiltInKeyWord, BuiltInKeyword::Function)) {
		fallback();
		return nullptr;
	}

	Token* retIdentifier = parseIdentifier();
	if (!retIdentifier) {
		throw std::runtime_error("Expect identifier after type identifier");
	}

	if (!tokenIsType(advance(), Token::Delimiter, Delimiter::LParen)) {
		throw std::runtime_error("Parameter list doesn't open with a left parenthesis");
	}

	std::unique_ptr<Statement> statement;
	auto func = std::make_unique<FunctionDeclaration>();
	func->identifierName = retIdentifier->str();
	Token* op;

	bool hasDefaultValue = false;
	std::unique_ptr<ASTNode> expression = nullptr;
	while (true) {
		VariableDeclType declType = parseDeclType();
		if (declType == VariableDeclType::Void) {
			fallback();
			return nullptr;
		}

		Token* type = parseIdentifier();
		if (!type) {
			throw std::runtime_error("Expect type identifier after declaration type");
		}

		Token* identifier = parseIdentifier();
		if (!identifier) {
			throw std::runtime_error("Expect identifier after type identifier");
		}
		
		VariableLifeTime varLifeTime = parseLifeTime();
		if (varLifeTime.type == VariableLifeTime::Line && varLifeTime.value <= 0) {
			throw std::runtime_error("Parameter lifetime cannot be negative lines");
		}
		else if (varLifeTime.type == VariableLifeTime::Scope && varLifeTime.value > 1) {
			throw std::runtime_error("Parameter lifetime cannot has scope lifetime greater than 1");
		}
		
		op = peek();

		expression = nullptr;
		if (tokenIsType(op, Token::Operator, Operator::Assignment)) {
			advance();
			expression = parseExpression();

			if (!expression) {
				throw std::runtime_error("Expect expression after assignment");
			}

			hasDefaultValue = true;
		}
		else if (hasDefaultValue) {
			throw std::runtime_error("Defaulted parameter cannot appear before undefaulted parameter");
		}

		func->parameters.push_back(
			{ declType, type->str(), identifier->str(), varLifeTime, std::move(expression) }
		);
		if (!tokenIsType(peek(), Token::Delimiter, Delimiter::Comma)) {
			break;
		}
		advance();
	}
	if (!tokenIsType(advance(), Token::Delimiter, Delimiter::RParen)) {
		throw std::runtime_error("Parameter list doesn't close with a right parenthesis");
	}

	VariableDeclType retDeclType = parseDeclType();
	if (retDeclType != VariableDeclType::Void) {
		Token* retType = parseIdentifier();
		if (!retType) {
			throw std::runtime_error("Expect type identifier after declaration type");
		}
		func->returnVarType = retType->str();
	}
	func->returnVarDeclType = retDeclType;

	func->block = parseBlock(0);
	if (!func->block) {
		throw std::runtime_error("Function isn't followed by a block");
	}
	statement = parseStatementType();
	statement->statement = std::move(func);
	return statement;
}

std::unique_ptr<Statement> AST::parseVariableDeclaration() {
	// declType type id<lifetime> (=exp), ...

	loadIndex();

	VariableDeclType declType = parseDeclType();
	if (declType == VariableDeclType::Void) {
		fallback();
		return nullptr;
	}

	Token* type = parseIdentifier();
	if (!type) {
		throw std::runtime_error("Expect type identifier after declaration type");
	}

	std::unique_ptr<Statement> statement;
	auto var = std::make_unique<VariableDeclaration>();
	var->variableDeclType = declType;
	var->variableType = type->str();
	Token* op;
	int priority = 0;

	while (true) {
		// Get all the declarations in the single line

		Token* identifier = parseIdentifier();
		if (!identifier) {
			throw std::runtime_error("Expect identifier after type identifier");
		}

		VariableLifeTime varLifeTime = parseLifeTime();
		op = peek();

		std::unique_ptr<ASTNode> expression = nullptr;
		if (tokenIsType(op, Token::Operator, Operator::Assignment)) {
			advance();
			expression = parseExpression();

			if (!expression) {
				throw std::runtime_error("Expect expression after assignment");
			}
		}

		var->declarations.push_back(
			{ declType, type->str(), identifier->str(), varLifeTime, std::move(expression) }
		);
		if (!tokenIsType(peek(), Token::Delimiter, Delimiter::Comma)) {
			break;
		}
		advance();
	}
	Token* terminator = advance();

	if (!tokenIsType(terminator, Token::StatementTerminator)) {
		// Variable declaration does not ends with '!'s or '?'
		statement = std::make_unique<NormalStatement>();
		priority = 0;
	}
	else if (tokenIsType(terminator, Token::StatementTerminator, StatementTerminator::ExclamationMark)) {
		// Variable declaration ends with '!'s
		priority = static_cast<StatementTerminator*>(terminator)->count;
		Token* debugTerminator = advance();

		if (tokenIsType(debugTerminator, Token::StatementTerminator, StatementTerminator::QuestionMark)) {
			// Variable declaration's '!'s are followed by '?'
			statement = std::make_unique<DebugStatement>();
		}
		else {
			statement = std::make_unique<NormalStatement>();
		}
	}
	else if (tokenIsType(terminator, Token::StatementTerminator, StatementTerminator::QuestionMark)) {
		// Variable declaration ends with '?'
		statement = std::make_unique<DebugStatement>();
		priority = 0;
	}
	var->priority = priority;
	statement->statement = std::move(var);
	return statement;
}

std::unique_ptr<ASTNode> AST::parseUnary() {
	loadIndex();
	Token* token = advance();
	if (isPrefixUnaryOperator(token)) {
		auto expr = std::make_unique<UnaryExpression>();
		expr->operatorType = static_cast<Operator::OperatorType>(token->valueType);
		expr->expression = parseUnary();
		return expr;
	}
	fallback();
	return parsePrimary();
}

std::unique_ptr<ASTNode> AST::parsePrimary() {
	// primary : Identifier | Literal (postfix operator) | LPAREN expr RPAREN 

	loadIndex();
	Token* token = advance();

	if (tokenIsType(token, Token::Identifier)) {
		if (isPostfixUnaryOperator(peek())) {
			auto expr = std::make_unique<UnaryExpression>();
			expr->operatorType = static_cast<Operator::OperatorType>(advance()->valueType);
			expr->expression = std::make_unique<IdentifierNode>(token);
			return expr;
		}
		return std::make_unique<IdentifierNode>(token);
	}
	else if (tokenIsType(token, Token::NumericLiteral, NumericLiteral::Interger)) {
		return std::make_unique<IntergerLiteralNode>(token);
	}
	else if (tokenIsType(token, Token::NumericLiteral, NumericLiteral::Float)) {
		return std::make_unique<FloatLiteralNode>(token);
	}
	else if (tokenIsType(token, Token::StringLiteral)) {
		return std::make_unique<StringLiteralNode>(token);
	}
	else if (tokenIsType(token, Token::Boolean)) {
		return std::make_unique<BooleanNode>(token);
	}
	else if (tokenIsType(token, Token::Delimiter, Delimiter::LParen)) {
		auto expr = parseExpression();
		if (tokenIsType(peek(), Token::Delimiter, Delimiter::RParen)) {
			advance();
		}
		return expr;
	}

	return nullptr;
}

std::unique_ptr<ASTNode> AST::parseExpression(int precedence) {
	auto left = parseUnary();
	Token* token;
	while ((token = peek()) && getPrecendence(token) > precedence) {
		advance();
		auto expr = std::make_unique<BinaryExpression>();
		expr->LExpression = std::move(left);
		expr->RExpression = parseExpression(getPrecendence(token));
		expr->operatorType = static_cast<Operator::OperatorType>(token->valueType);
		left = std::move(expr);
	}
	return left;
}

std::unique_ptr<ASTNode> AST::parseExpressionStatement() {
	loadIndex();
	auto expr = parseExpression();
	if (!expr) {
		fallback();
		return nullptr;
	}
	auto statement = parseStatementType();
	statement->statement = std::move(expr);
	return statement;
}

std::unique_ptr<Statement> AST::parseIfStatement() {
	loadIndex();

	if (!tokenIsType(advance(), Token::BuiltInKeyWord, BuiltInKeyword::If)) {
		fallback();
		return nullptr;
	}

	auto ifstatement = std::make_unique<IfStatement>();
	ifstatement->condition = parseExpression();
	if (!ifstatement->condition) {
		ifstatement->condition = std::make_unique<BooleanNode>(Boolean::True);
	}

	ifstatement->body = parseBlock(0);
	if (!ifstatement->body) {
		throw std::runtime_error("If statement isn't followed by a block");
	}
	auto statement = parseStatementType();
	statement->statement = std::move(ifstatement);
	return statement;
}

std::unique_ptr<Statement> AST::parseReverseStatement() {
	loadIndex();
	if (!tokenIsType(advance(), Token::BuiltInKeyWord, BuiltInKeyword::Reverse)) {
		fallback();
		return nullptr;
	}
	auto statement = parseStatementType();
	statement->statement = std::make_unique<ReverseStatement>();
	return statement;
}

std::unique_ptr<Statement> AST::parseReturnStatement() {
	loadIndex();
	Token* token = advance();
	if (!tokenIsType(token, Token::BuiltInKeyWord, BuiltInKeyword::Return)) {
		fallback();
		return nullptr;
	}
	auto retStatement = std::make_unique<ReturnStatement>();
	retStatement->expression = parseExpression();
	auto statement = parseStatementType();
	statement->statement = std::move(retStatement);

	return statement;
}

std::unique_ptr<Statement> AST::parseStatementType() {
	loadIndex();

	std::unique_ptr<Statement> statement = nullptr;
	if (tokenIsType(peek(), Token::StatementTerminator, StatementTerminator::QuestionMark)) {
		advance();
		statement = std::make_unique<DebugStatement>();
	}
	else if (tokenIsType(peek(), Token::StatementTerminator, StatementTerminator::ExclamationMark)) {
		advance();
		if (tokenIsType(peek(), Token::StatementTerminator, StatementTerminator::QuestionMark)) {
			advance();
			statement = std::make_unique<DebugStatement>();
		}
		else {
			statement = std::make_unique<NormalStatement>();
		}
	}
	else {
		statement = std::make_unique<NormalStatement>();
	}

	return statement;
}

void AST::skipStatementTerminator() {
	while (match(Token::Delimiter)) {
		advance();
	}
}

VariableDeclType AST::getVariableDeclType(Token* token) const {
	switch (token->valueType) {
	case BuiltInKeyword::VarVarVar:
		return VariableDeclType::VarVarVar;
	case BuiltInKeyword::VarVarConst:
		return VariableDeclType::VarVarConst;
	case BuiltInKeyword::VarConstVar:
		return VariableDeclType::VarConstVar;
	case BuiltInKeyword::VarConstConst:
		return VariableDeclType::VarConstConst;
	case BuiltInKeyword::ConstVarVar:
		return VariableDeclType::ConstVarVar;
	case BuiltInKeyword::ConstVarConst:
		return VariableDeclType::ConstVarConst;
	case BuiltInKeyword::ConstConstVar:
		return VariableDeclType::ConstConstVar;
	case BuiltInKeyword::ConstConstConst:
		return VariableDeclType::ConstConstConst;
	}
}

int AST::getPrecendence(Token* token) const {
	if (!token->isType(Token::Operator)) {
		return -1;
	}
	return s_presedence.at(static_cast<Operator::OperatorType>(token->valueType));
}

bool AST::isAssignmentOperator(Token* token) const {
	return token && token->type == Token::Operator 
		&& (token->valueType == Operator::Assignment
			|| token->valueType == Operator::AdditionAssignment
			|| token->valueType == Operator::SubtractionAssignment
			|| token->valueType == Operator::MultiplicationAssignment
			|| token->valueType == Operator::DivisionAssignment
			|| token->valueType == Operator::ModulusAssignment
			|| token->valueType == Operator::ExponentiationAssignment);
}

bool AST::isUnaryOperator(Token* token) const {
	return isPrefixUnaryOperator(token) || isPostfixUnaryOperator(token);
}
bool AST::isPrefixUnaryOperator(Token* token) const {
	return token && token->isType(Token::Operator) &&
		(token->valueType == Operator::UnaryPlus
			|| token->valueType == Operator::UnaryNegation
			|| token->valueType == Operator::UnaryAbs);
}
bool AST::isPostfixUnaryOperator(Token* token) const {
	return token && token->isType(Token::Operator) &&
		(token->valueType == Operator::FrontIncrement
			|| token->valueType == Operator::EndIncrement
			|| token->valueType == Operator::FrontDecrement
			|| token->valueType == Operator::EndDecrement);
}

bool AST::tokenIsType(Token* token, Token::TokenType type) const {
	return token && token->isType(type);
}

bool AST::tokenIsType(Token* token, Token::TokenType type, int valueType) const {
	return token && token->isType(type, valueType);
}
