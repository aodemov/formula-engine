#include "engine.h"

#include "ast-node.h"

namespace formulaEngine {
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
  }

int Engine::Evaluate(std::string& expression) {
  auto node = parser_->Parse(expression);
  return EvaluateNode(node);
}

int Engine::EvaluateNode(AstNode* node) {
  auto type = node->type();

  EvaluationFunction func = evaluationMap.at(type);
  return (this->*func)(node);
}

int Engine::EvaluateNumber(AstNode* node) {
  auto n = dynamic_cast<NumberNode*>(node);

  return n->value();
}

int Engine::EvaluateAddition(AstNode* node) {
  auto n = dynamic_cast<BinaryOperatorNode*>(node);
  auto left = EvaluateNode(n->left());
  auto right = EvaluateNode(n->right());

  return left + right;
}

int Engine::EvaluateSubtraction(AstNode* node) {
  auto n = dynamic_cast<BinaryOperatorNode*>(node);
  auto left = EvaluateNode(n->left());
  auto right = EvaluateNode(n->right());

  return left - right;
}

int Engine::EvaluateMultiplication(AstNode* node) {
  auto n = dynamic_cast<BinaryOperatorNode*>(node);
  auto left = EvaluateNode(n->left());
  auto right = EvaluateNode(n->right());

  return left * right;
}

int Engine::EvaluateDivision(AstNode* node) {
  auto n = dynamic_cast<BinaryOperatorNode*>(node);
  auto left = EvaluateNode(n->left());
  auto right = EvaluateNode(n->right());

  return left / right;
}

int Engine::EvaluateModulus(AstNode* node) {
  auto n = dynamic_cast<BinaryOperatorNode*>(node);
  auto left = EvaluateNode(n->left());
  auto right = EvaluateNode(n->right());

  return left % right;
}

}