#include "gtest/gtest.h"
#include "lexer.h"

#include <vector>
#include <tuple>
#include <string>
#include <iostream>
#include <memory>

TEST(LexerTest, BasicCase){
  using namespace std;
  using namespace formulaEngine;

  // Token type, value, beginPosition, endPosition
  vector<tuple<Token::TokenType, string, size_t, size_t>> v = {
    make_tuple(Token::NUMBER, "12", 0, 2),
    make_tuple(Token::SLASH, "/", 3, 4),
    make_tuple(Token::NUMBER, "205", 4, 7),
    make_tuple(Token::PERCENT, "%", 7, 8),
    make_tuple(Token::NUMBER, "1", 9, 10),
    make_tuple(Token::EOE, "EOE", 10, 10),
    make_tuple(Token::EOE, "EOE", 10, 10),
  };

  string input = "12 /205% 1";
  formulaEngine::Lexer lexer(make_unique<Scanner>(input));

  for(auto it = v.begin(); it != v.end(); it++) {
    auto tok = lexer.ReadNext();
    ASSERT_EQ(tok.type, get<0>(*it));
    ASSERT_EQ(tok.value, get<1>(*it));
    ASSERT_EQ(tok.beginPosition, get<2>(*it));
    ASSERT_EQ(tok.endPosition, get<3>(*it));
  }
}

TEST(LexerTest, NewLine){
  using namespace std;
  using namespace formulaEngine;

  // Token type, value, beginPosition, endPosition
  vector<tuple<Token::TokenType, string, size_t, size_t>> v = {
    make_tuple(Token::NUMBER, "453", 0, 3),
    make_tuple(Token::NUMBER, "5", 7, 8),
    make_tuple(Token::EOE, "EOE", 8, 8),
    make_tuple(Token::EOE, "EOE", 8, 8),
  };

  string input = "453 \n\r 5";
  formulaEngine::Lexer lexer(make_unique<Scanner>(input));

  for(auto it = v.begin(); it != v.end(); it++) {
    auto tok = lexer.ReadNext();
    ASSERT_EQ(tok.type, get<0>(*it));
    ASSERT_EQ(tok.value, get<1>(*it));
    ASSERT_EQ(tok.beginPosition, get<2>(*it));
    ASSERT_EQ(tok.endPosition, get<3>(*it));
  }
}


TEST(LexerTest, Spaces){
  using namespace std;
  using namespace formulaEngine;

  // Token type, value, beginPosition, endPosition
  vector<tuple<Token::TokenType, string, size_t, size_t>> v = {
    make_tuple(Token::NUMBER, "453", 0, 3),
    make_tuple(Token::NUMBER, "5", 17, 18),
    make_tuple(Token::EOE, "EOE", 23, 23),
    make_tuple(Token::EOE, "EOE", 23, 23),
  };

  string input = "453              5     ";
  formulaEngine::Lexer lexer(make_unique<Scanner>(input));

  for(auto it = v.begin(); it != v.end(); it++) {
    auto tok = lexer.ReadNext();
    ASSERT_EQ(tok.type, get<0>(*it));
    ASSERT_EQ(tok.value, get<1>(*it));
    ASSERT_EQ(tok.beginPosition, get<2>(*it));
    ASSERT_EQ(tok.endPosition, get<3>(*it));
  }
}