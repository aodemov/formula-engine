#pragma once

#include "parser.h"
#include <map>

#include <string>

namespace formulaEngine {

typedef double (*EvaluationFunction)(AstNode*);

class Engine {
public:
  static double Evaluate(std::string& expression);

private:
  static double EvaluateNode(AstNode* node);

  static double EvaluateNumber(AstNode* node);
  static double EvaluateAddition(AstNode* node);
  static double EvaluateSubtraction(AstNode* node);
  static double EvaluateMultiplication(AstNode* node);
  static double EvaluateDivision(AstNode* node);
  static double EvaluateModulus(AstNode* node);
  static double EvaluateNegation(AstNode* node);
  static double EvaluateFactorial(AstNode* node);
  static double EvaluateExponent(AstNode* node);

  static Parser* parser_;
  static AstAllocator* allocator_;
  static std::map<AstNode::AstNodeType, EvaluationFunction> evaluationMap;
};
}
