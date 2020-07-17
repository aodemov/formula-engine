#pragma once

#include <string>

#include "token.h"

namespace formulaEngine{

class AstNodeFactory;
class AstAllocator;

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

  AstNode(const AstNode& other) = delete;
  void operator=(const AstNode& other) = delete;

  const Token& token() const {
    return token_;
  }

  AstNodeType type() const {
    return type_;
  }

protected:
  friend class AstNodeFactory;
  friend class AstAllocator;

  explicit AstNode(Token token, AstNodeType type)
    : token_(token),
      type_(type)
    {}

  Token token_;
  AstNodeType type_;
  virtual bool Polymorphic() = 0;
};

class NumberNode : public AstNode {
public:
  int value() const {
    return value_;
  }

protected:
  friend class AstNodeFactory;
  friend class AstAllocator;

  explicit NumberNode(Token token, AstNodeType type)
  : AstNode(token, type)
  {
    value_ = std::stoi(token_.value);
  }

  int value_;
  virtual bool Polymorphic() {
    return true;
  }
};

class Expression : public AstNode {
public:
protected:
  friend class AstNodeFactory;
  friend class AstAllocator;

  explicit Expression(Token token, AstNodeType type)
    : AstNode(token, type)
    {}

  virtual bool Polymorphic() {
    return true;
  }
};

class BinaryOperatorNode : public Expression {
public:
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


protected:
  friend class AstNodeFactory;
  friend class AstAllocator;

  explicit BinaryOperatorNode(Token token, AstNodeType type, AstNode* left, AstNode* right)
    : Expression(token, type),
      left_(left),
      right_(right)
    {}

  AstNode* left_;
  AstNode* right_;

  virtual bool Polymorphic() {
    return true;
  }
};
}