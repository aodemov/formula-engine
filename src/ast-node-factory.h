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