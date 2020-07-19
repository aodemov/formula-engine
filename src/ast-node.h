#pragma once

#include <string>

#include "token.h"

namespace formulaEngine{

class AstNodeFactory;
class AstAllocator;

class AstNode {
public:
  enum AstNodeType {
    ADD,    // Addition
    SUB,    // Subtraction
    MUL,    // Multiplication
    DIV,    // Division
    MOD,    // Modulus
    NEG,    // Unary negation
    FAC,    // Factorial
    EXP,    // Exponent
    NUMBER  // Number
  };

  AstNode(const AstNode& other) = delete;
  void operator=(const AstNode& other) = delete;

  AstNodeType type() const {
    return type_;
  }

protected:
  friend class AstNodeFactory;
  friend class AstAllocator;

  explicit AstNode(AstNodeType type)
    : type_(type)
    {}

  AstNodeType type_;
  virtual bool Polymorphic() = 0;
};

class Expression : public AstNode {
public:
protected:
  friend class AstNodeFactory;
  friend class AstAllocator;

  explicit Expression(AstNodeType type)
    : AstNode(type)
    {}

  virtual bool Polymorphic() {
    return true;
  }
};

class NumberNode : public AstNode {
public:
  double value() const {
    return value_;
  }

protected:
  friend class AstNodeFactory;
  friend class AstAllocator;

  explicit NumberNode(AstNodeType type, double value)
  : AstNode(type),
    value_(value)
  {}

  double value_;
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

  explicit BinaryOperatorNode(AstNodeType type, AstNode* left, AstNode* right)
    : Expression(type),
      left_(left),
      right_(right)
    {}

  AstNode* left_;
  AstNode* right_;

  virtual bool Polymorphic() {
    return true;
  }
};

class UnaryOperatorNode : public Expression {
public:
  AstNode* operand() const {
    return operand_;
  }

  ~UnaryOperatorNode() {
    delete operand_;
  }

protected:
  friend class AstNodeFactory;
  friend class AstAllocator;

  explicit UnaryOperatorNode(AstNodeType type, AstNode* operand)
    : Expression(type),
      operand_(operand)
    {}

  AstNode* operand_;

  virtual bool Polymorphic() {
    return true;
  }
};
}