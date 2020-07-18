#pragma once

#include "ast-allocator.h"
#include "ast-node.h"

namespace formulaEngine {
class AstNodeFactory {
public:
  AstNodeFactory(AstAllocator* allocator)
    : allocator_(allocator)
    {}

  AstNodeFactory(const AstNodeFactory& other) = delete;
  AstNodeFactory& operator=(const AstNodeFactory& other) = delete;

  NumberNode* NewNumberNode(AstNode::AstNodeType type, double value) {
    return allocator_->New<NumberNode>(type, value);
  }

  BinaryOperatorNode* NewBinaryOperatorNode(AstNode::AstNodeType type, AstNode* left, AstNode* right) {
    return allocator_->New<BinaryOperatorNode>(type, left, right);
  }

private:
  AstAllocator* allocator_;
};
}