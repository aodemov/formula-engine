#include "parser.h"

#include <memory>

#include "parsing-exception.h"

namespace formulaEngine {
AstNode* Parser::Parse(std::string& buffer) {
  lexer = new Lexer(std::make_unique<Scanner>(buffer));

  return ParseExpression();
}

AstNode* Parser::ParseExpression() {
  auto left = ParseTerm();

  auto next = lexer->Peek();
  while (next.type == Token::PLUS || next.type == Token::MINUS) {
    next = lexer->ReadNext();

    auto right = ParseTerm();

    AstNode::AstNodeType nodeType;
    switch(next.type){
      case Token::PLUS:    nodeType = AstNode::MUL; break;
      case Token::MINUS:   nodeType = AstNode::DIV; break;
    }

    left = new BinaryOperatorNode(next, nodeType, left, right);

    next = lexer->Peek();
  }

  return left;
}

AstNode* Parser::ParseTerm() {
  auto left = ParseFactor();

  auto next = lexer->Peek();
  while (next.type == Token::STAR || next.type == Token::SLASH || next.type == Token::PERCENT) {
    next = lexer->ReadNext();

    auto right = ParseFactor();

    AstNode::AstNodeType nodeType;
    switch(next.type){
      case Token::STAR:    nodeType = AstNode::MUL; break;
      case Token::SLASH:   nodeType = AstNode::DIV; break;
      case Token::PERCENT: nodeType = AstNode::MOD; break;
    }

    left = new BinaryOperatorNode(next, nodeType, left, right);
    
    next = lexer->Peek();
  }

  return left;
}

AstNode* Parser::ParseFactor() {
  return ParseNumber();
}

AstNode* Parser::ParseNumber() {
  Expect(Token::NUMBER);
  return new NumberNode(lexer->ReadNext(), AstNode::NUMBER);
}


void Parser::Expect(Token::TokenType type) {
  auto t = lexer->Peek();
  if(t.type != type)
    throw ParsingException(t.value, t.beginPosition, t.endPosition);
}

}