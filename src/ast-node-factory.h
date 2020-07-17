#pragma once

#include "ast-allocator.h"
#include "ast-node.h"

namespace formulaEngine {
class AstNodeFactory {
public:
  AstNodeFactory()
    : allocator_(new AstAllocator())
    {}

  NumberNode* NewNumberNode(Token token, AstNode::AstNodeType type) {
    return allocator_->New<NumberNode>(token, type);
  }

  BinaryOperatorNode* NewBinaryOperatorNode(Token token, AstNode::AstNodeType type, AstNode* left, AstNode* right) {
    return allocator_->New<BinaryOperatorNode>(token, type, left, right);
  }

private:
  AstAllocator* allocator_;
};
}