#pragma once

#include <string>

#include "lexer.h"
#include "ast-node.h"

namespace formulaEngine {
class Parser {
public:
  explicit Parser()
    : lexer(nullptr)
    {}

  AstNode* Parse(std::string& buffer);

private:
  Lexer* lexer;
  
  AstNode* ParseExpression();
  AstNode* ParseTerm();
  AstNode* ParseFactor();
  AstNode* ParseNumber();

  void Expect(Token::TokenType);
};
}