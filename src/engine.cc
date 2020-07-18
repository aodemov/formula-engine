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

Engine::Engine()
  {
    allocator_ = new AstAllocator();
    parser_ = new Parser(allocator_);

    evaluationMap[AstNode::ADD] = &EvaluateAddition;
    evaluationMap[AstNode::SUB] = &EvaluateSubtraction;
    evaluationMap[AstNode::MUL] = &EvaluateMultiplication;
    evaluationMap[AstNode::DIV] = &EvaluateDivision;
    evaluationMap[AstNode::MOD] = &EvaluateModulus;
    evaluationMap[AstNode::NUMBER] = &EvaluateNumber;
    evaluationMap[AstNode::NEG] = &EvaluateNegation;
    evaluationMap[AstNode::FAC] = &EvaluateFactorial;
  }

double Engine::Evaluate(std::string& expression) {
  auto node = parser_->Parse(expression);
  double result = EvaluateNode(node);
  allocator_->DeleteAll();
  return result;
}

double Engine::EvaluateNode(AstNode* node) {
  auto type = node->type();

  EvaluationFunction func = evaluationMap.at(type);
  return (this->*func)(node);
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

}