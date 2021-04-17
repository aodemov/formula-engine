#include "engine.h"

#include "ast-node.h"

#include <cmath>

namespace formulaEngine {
int factorial(int n)
{
  if (n < 0)
    return 0;
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

std::map<AstNode::AstNodeType, EvaluationFunction> Engine::evaluationMap = {
  { AstNode::ADD, &EvaluateAddition },
  { AstNode::SUB, &EvaluateSubtraction },
  { AstNode::MUL, &EvaluateMultiplication },
  { AstNode::DIV, &EvaluateDivision },
  { AstNode::MOD, &EvaluateModulus },
  { AstNode::NEG, &EvaluateNegation },
  { AstNode::FAC, &EvaluateFactorial },
  { AstNode::EXP, &EvaluateExponent },
  { AstNode::NUMBER, &EvaluateNumber},
};

AstAllocator* Engine::allocator_ = nullptr;
Parser* Engine::parser_ = nullptr;


double Engine::Evaluate(std::string& expression) {
  allocator_ = new AstAllocator();
  parser_ = new Parser(allocator_);

  auto node = parser_->Parse(expression);
  double result = EvaluateNode(node);
  allocator_->DeleteAll();
  return result;
}

double Engine::EvaluateNode(AstNode* node) {
  auto type = node->type();

  EvaluationFunction func = evaluationMap.at(type);
  return (*func)(node);
}

double Engine::EvaluateNumber(AstNode* node) {
  auto n = dynamic_cast<NumberNode*>(node);

  return n->value();
}

double Engine::EvaluateAddition(AstNode* node) {
  auto n = dynamic_cast<BinaryOperatorNode*>(node);
  auto left = EvaluateNode(n->left());
  auto right = EvaluateNode(n->right());

  return left + right;
}

double Engine::EvaluateSubtraction(AstNode* node) {
  auto n = dynamic_cast<BinaryOperatorNode*>(node);
  auto left = EvaluateNode(n->left());
  auto right = EvaluateNode(n->right());

  return left - right;
}

double Engine::EvaluateMultiplication(AstNode* node) {
  auto n = dynamic_cast<BinaryOperatorNode*>(node);
  auto left = EvaluateNode(n->left());
  auto right = EvaluateNode(n->right());

  return left * right;
}

double Engine::EvaluateDivision(AstNode* node) {
  auto n = dynamic_cast<BinaryOperatorNode*>(node);
  auto left = EvaluateNode(n->left());
  auto right = EvaluateNode(n->right());

  return left / right;
}

double Engine::EvaluateModulus(AstNode* node) {
  auto n = dynamic_cast<BinaryOperatorNode*>(node);
  auto left = EvaluateNode(n->left());
  auto right = EvaluateNode(n->right());

  return std::fmod(left, right);
}

double Engine::EvaluateNegation(AstNode* node) {
  auto n = dynamic_cast<UnaryOperatorNode*>(node);
  auto op = EvaluateNode(n->operand());

  return -op;
}

double Engine::EvaluateFactorial(AstNode* node) {
  auto n = dynamic_cast<UnaryOperatorNode*>(node);
  auto op = EvaluateNode(n->operand());

  return factorial(static_cast<int>(op));
}

double Engine::EvaluateExponent(AstNode* node) {
  auto n = dynamic_cast<BinaryOperatorNode*>(node);
  auto left = EvaluateNode(n->left());
  auto right = EvaluateNode(n->right());

  return std::pow(left, right);
}

}
