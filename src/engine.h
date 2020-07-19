#pragma once

#include "parser.h"
#include <map>

#include <string>

namespace formulaEngine {
class Engine {
public:
  typedef double (Engine::*EvaluationFunction)(AstNode*);

  explicit Engine();

  ~Engine() {
    delete parser_;
    delete allocator_;
  }

  double Evaluate(std::string& expression);

private:
  double EvaluateNode(AstNode* node);

  double EvaluateNumber(AstNode* node);
  double EvaluateAddition(AstNode* node);
  double EvaluateSubtraction(AstNode* node);
  double EvaluateMultiplication(AstNode* node);
  double EvaluateDivision(AstNode* node);
  double EvaluateModulus(AstNode* node);
  double EvaluateNegation(AstNode* node);
  double EvaluateFactorial(AstNode* node);
  double EvaluateExponent(AstNode* node);

  Parser* parser_;
  AstAllocator* allocator_;
  std::map<AstNode::AstNodeType, EvaluationFunction> evaluationMap;
};
}