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

  explicit AstNode(Token token, AstNodeType type)
    : token_(token),
      type_(type)
    {}

  AstNode(const AstNode& other) = delete;
  void operator=(const AstNode& other) = delete;

  const Token& token() const {
    return token_;
  }

  AstNodeType type() const {
    return type_;
  }

protected:
  Token token_;
  AstNodeType type_;
  virtual bool Polymorphic() = 0;
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
  virtual bool Polymorphic() {
    return true;
  }
};

class OperatorNode : public AstNode {
public:
  explicit OperatorNode(Token token, AstNodeType type)
    : AstNode(token, type)
    {}

private:
  virtual bool Polymorphic() {
    return true;
  }
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

  ~BinaryOperatorNode() {
    delete left_;
    delete right_;
  }


private:
  AstNode* left_;
  AstNode* right_;

  virtual bool Polymorphic() {
    return true;
  }
};
}