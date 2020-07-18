#pragma once

#include <string>

#include "lexer.h"
#include "ast-node.h"
#include "ast-node-factory.h"

namespace formulaEngine {
class Parser {
public:
  explicit Parser(AstAllocator* allocator)
    : lexer_(nullptr),
      factory_(new AstNodeFactory(allocator))
    {}

  Parser(const Parser& other) = delete;
  Parser& operator=(const Parser& other) = delete;

  AstNode* Parse(std::string& buffer);

  ~Parser() {
    delete factory_;
    delete lexer_;
  }

private:
  Lexer* lexer_;
  AstNodeFactory* factory_;
  
  AstNode* ParseExpression();
  AstNode* ParseTerm();
  AstNode* ParseFactor();
  AstNode* ParsePrimary();
  AstNode* ParseSubexpression();
  AstNode* ParseNumber();

  bool IsNext(Token::TokenType);
  void Expect(Token::TokenType);
};
}