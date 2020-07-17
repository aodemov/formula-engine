#pragma once

#include "parser.h"
#include <map>

#include <string>

namespace formulaEngine {
class Engine {
public:
  typedef int (Engine::*EvaluationFunction)(AstNode*);

  explicit Engine();

  ~Engine() {
    delete parser_;
    delete allocator_;
  }

  int Evaluate(std::string& expression);

private:
  int EvaluateNode(AstNode* node);

  int EvaluateNumber(AstNode* node);
  int EvaluateAddition(AstNode* node);
  int EvaluateSubtraction(AstNode* node);
  int EvaluateMultiplication(AstNode* node);
  int EvaluateDivision(AstNode* node);
  int EvaluateModulus(AstNode* node);

  Parser* parser_;
  AstAllocator* allocator_;
  std::map<AstNode::AstNodeType, EvaluationFunction> evaluationMap;
};
}