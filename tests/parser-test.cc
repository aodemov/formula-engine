#include "gtest/gtest.h"
#include "parser.h"

#include <vector>
#include <tuple>
#include <string>
#include <iostream>

TEST(ParserTest, Plus){
  //Expected Tree
  //
  //              BinaryOperator(+)
  //               /            \
  //       Number(1)            Number(2)

  using namespace std;
  using namespace formulaEngine;

  string input = "1 + 2";
  AstAllocator* allocator = new AstAllocator();
  auto parser = new Parser(allocator);

  auto ast = parser->Parse(input);

  ASSERT_FALSE(ast == nullptr);

  ASSERT_EQ(ast->type(), AstNode::ADD);

  cout << to_string(ast->type()) << endl;
  
  BinaryOperatorNode* astOp;
  ASSERT_NO_THROW(astOp = dynamic_cast<BinaryOperatorNode*>(ast));

  ASSERT_EQ(astOp->left()->type(), AstNode::NUMBER);
  ASSERT_EQ(astOp->right()->type(), AstNode::NUMBER);

  NumberNode* left;
  NumberNode* right;
  ASSERT_NO_THROW(left = dynamic_cast<NumberNode*>(astOp->left()));
  ASSERT_NO_THROW(right = dynamic_cast<NumberNode*>(astOp->right()));

  ASSERT_EQ(left->value(), 1);
  ASSERT_EQ(right->value(), 2);

  delete allocator;
}

TEST(ParserTest, PlusMultiply){
  //Expected Tree
  //            BinaryOperator(+)
  //            /               \
  //       Number(1)        BinaryOperator(*)
  //                          /         \
  //                     Number(2)    Number(3)

  using namespace std;
  using namespace formulaEngine;

  string input = "1 + 2 * 3";
  AstAllocator* allocator = new AstAllocator();
  auto parser = new Parser(allocator);
  auto ast = parser->Parse(input);

  ASSERT_FALSE(ast == nullptr);

  ASSERT_EQ(ast->type(), AstNode::ADD);
  
  // Check root
  BinaryOperatorNode* astOp;
  ASSERT_NO_THROW(astOp = dynamic_cast<BinaryOperatorNode*>(ast));

  // Check left number
  ASSERT_EQ(astOp->left()->type(), AstNode::NUMBER);
  NumberNode* left;
  ASSERT_NO_THROW(left = dynamic_cast<NumberNode*>(astOp->left()));
  ASSERT_EQ(left->value(), 1);

  // Check right tree
  ASSERT_EQ(astOp->right()->type(), AstNode::MUL);
  BinaryOperatorNode* right;
  ASSERT_NO_THROW(right = dynamic_cast<BinaryOperatorNode*>(astOp->right()));

  // Check right's left
  ASSERT_EQ(right->left()->type(), AstNode::NUMBER);
  NumberNode* rights_left;
  ASSERT_NO_THROW(rights_left = dynamic_cast<NumberNode*>(right->left()));
  ASSERT_EQ(rights_left->value(), 2);

  // Check right's right
  ASSERT_EQ(right->right()->type(), AstNode::NUMBER);
  NumberNode* rights_right;
  ASSERT_NO_THROW(rights_right = dynamic_cast<NumberNode*>(right->right()));
  ASSERT_EQ(rights_right->value(), 3);

  delete allocator;
}