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

  auto next = lexer_->Peek();
  while (next.type == Token::PLUS || next.type == Token::MINUS) {
    next = lexer_->ReadNext();

    auto right = ParseTerm();

    AstNode::AstNodeType nodeType;
    switch(next.type){
      case Token::PLUS:    nodeType = AstNode::ADD; break;
      case Token::MINUS:   nodeType = AstNode::SUB; break;
    }

    left = factory_->NewBinaryOperatorNode(nodeType, left, right);

    next = lexer_->Peek();
  }

  return left;
}

AstNode* Parser::ParseTerm() {
  auto left = ParseFactor();

  auto next = lexer_->Peek();
  while (next.type == Token::STAR || next.type == Token::SLASH || next.type == Token::PERCENT) {
    next = lexer_->ReadNext();

    auto right = ParseFactor();

    AstNode::AstNodeType nodeType;
    switch(next.type){
      case Token::STAR:    nodeType = AstNode::MUL; break;
      case Token::SLASH:   nodeType = AstNode::DIV; break;
      case Token::PERCENT: nodeType = AstNode::MOD; break;
    }

    left = factory_->NewBinaryOperatorNode(nodeType, left, right);
    
    next = lexer_->Peek();
  }

  return left;
}

AstNode* Parser::ParseFactor() {
  return ParseNumber();
}

AstNode* Parser::ParseNumber() {
  Expect(Token::NUMBER);
  Token token = lexer_->ReadNext();
  double value = std::stod(token.value);
  return factory_->NewNumberNode(AstNode::NUMBER, value);
}


void Parser::Expect(Token::TokenType type) {
  auto t = lexer_->Peek();
  if(t.type != type)
    throw ParsingException(t.value, t.beginPosition, t.endPosition);
}

}