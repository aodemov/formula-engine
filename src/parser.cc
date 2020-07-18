#include "parser.h"

#include <memory>
#include <string>

#include "parsing-exception.h"

namespace formulaEngine {
AstNode* Parser::Parse(std::string& buffer) {
  lexer_ = new Lexer(std::make_unique<Scanner>(buffer));

  return ParseExpression();
}

AstNode* Parser::ParseExpression() {
  auto left = ParseTerm();

  auto next = lexer_->Peek().type;
  while (next == Token::PLUS || next == Token::MINUS) {
    lexer_->ReadNext();

    auto right = ParseTerm();

    AstNode::AstNodeType nodeType;
    switch(next){
      case Token::PLUS:    nodeType = AstNode::ADD; break;
      case Token::MINUS:   nodeType = AstNode::SUB; break;
    }

    left = factory_->NewBinaryOperatorNode(nodeType, left, right);

    next = lexer_->Peek().type;
  }

  return left;
}

AstNode* Parser::ParseTerm() {
  auto left = ParseFactor();

  auto next = lexer_->Peek().type;
  while (next == Token::STAR || next == Token::SLASH || next == Token::PERCENT) {
    lexer_->ReadNext();

    auto right = ParseFactor();

    AstNode::AstNodeType nodeType;
    switch(next){
      case Token::STAR:    nodeType = AstNode::MUL; break;
      case Token::SLASH:   nodeType = AstNode::DIV; break;
      case Token::PERCENT: nodeType = AstNode::MOD; break;
    }

    left = factory_->NewBinaryOperatorNode(nodeType, left, right);
    
    next = lexer_->Peek().type;
  }

  return left;
}

AstNode* Parser::ParseFactor() {
  AstNode* node = nullptr;

  if (IsNext(Token::MINUS)) {
    lexer_->ReadNext();
    auto operand = ParseFactor();
    node = factory_->NewUnaryOperatorNode(AstNode::NEG, operand);
  } else {
    node = ParsePrimary();
  }

  if (IsNext(Token::EXCL)) {
    lexer_->ReadNext();
    node = factory_->NewUnaryOperatorNode(AstNode::FAC, node);
  }

  return node;
}

AstNode* Parser::ParsePrimary() {
  if (IsNext(Token::LPAREN)) {
    return ParseSubexpression();
  } else {
    return ParseNumber();
  }
}

AstNode* Parser::ParseNumber() {
  Expect(Token::NUMBER);
  Token token = lexer_->ReadNext();
  double value = std::stod(token.value);
  return factory_->NewNumberNode(AstNode::NUMBER, value);
}

AstNode* Parser::ParseSubexpression() {
  Expect(Token::LPAREN);
  lexer_->ReadNext();

  auto node = ParseExpression();

  Expect(Token::RPAREN);
  lexer_->ReadNext();

  return node;
}


bool Parser::IsNext(Token::TokenType type) {
  return lexer_->Peek().type == type;
}

void Parser::Expect(Token::TokenType type) {
  auto t = lexer_->Peek();
  if(t.type != type)
    throw ParsingException(t.value, t.beginPosition, t.endPosition);
}

}