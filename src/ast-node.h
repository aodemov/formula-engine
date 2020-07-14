#pragma once

#include <string>

#include "token.h"

namespace formulaEngine{
class AstNode {
public:
  enum AstNodeType {
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    NUMBER
  };

  const Token& token() const {
    return token_;
  }

  AstNodeType type() const {
    return type_;
  }

  explicit AstNode(Token token, AstNodeType type)
    : token_(token),
      type_(type)
    {}

protected:
  Token token_;
  AstNodeType type_;
};

class NumberNode : public AstNode {
public:
  explicit NumberNode(Token token, AstNodeType type)
    : AstNode(token, type)
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
  explicit OperatorNode(Token token, AstNodeType type)
    : AstNode(token, type)
    {}
};

class BinaryOperatorNode : public OperatorNode {
public:
  explicit BinaryOperatorNode(Token token, AstNodeType type, AstNode* left, AstNode* right)
    : OperatorNode(token, type),
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