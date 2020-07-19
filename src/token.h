#pragma once

#include <cstddef>
#include <cstdint>

#include <string>
#include <limits>

namespace formulaEngine {

class Token {
public:
  enum TokenType {
    UNINITIALIZED,
    EOE,        // End of expression
    ILLEGAL,

    PLUS,       // +
    MINUS,      // -
    STAR,       // *
    SLASH,      // /
    PERCENT,    // %

    EXCL,       // !
    CARET,      // ^

    POINT,      // .

    LPAREN,     // (
    RPAREN,     // )

    NUMBER,     // real number

    WHITESPACE, // whitespace
  };

  size_t beginPosition;
  size_t endPosition;
  std::string value;
  TokenType type;

  explicit Token (size_t beginPosition, size_t endPosition, std::string value, TokenType type)
    : beginPosition(beginPosition),
      endPosition(endPosition),
      value(value),
      type(type)
    {}

  explicit Token()
    : beginPosition(std::numeric_limits<size_t>::max()),
      endPosition(std::numeric_limits<size_t>::max()),
      value(""),
      type(Token::UNINITIALIZED)
      {}
};

} // namespase formulaEngine