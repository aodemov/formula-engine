#pragma once

#include <string>

#include "token.h"

namespace formulaEngine{
class AstNode {
public:
  const Token& token() const {
    return token_;
  }

  explicit AstNode(Token token)
    : token_(token)
    {}

protected:
  Token token_;
};

class NumberNode : public AstNode {
public:
  explicit NumberNode(Token token)
    : AstNode(token)
    {
      value_ = std::stoi(token_.value);
    }

  int value() const {
    return value_;
  }

private:
  int value_;
};

class OperatorNode : public AstNode {
public:
  explicit OperatorNode(Token token)
    : AstNode(token)
    {}
};

class BinaryOperatorNode : public OperatorNode {
public:
  explicit BinaryOperatorNode(Token token, AstNode* left, AstNode* right)
    : OperatorNode(token),
      left_(left),
      right_(right)
    {}

  AstNode* left() const {
    return left_;
  }

  AstNode* right() const {
    return right_;
  }


private:
  AstNode* left_;
  AstNode* right_;
};
}