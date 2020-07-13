#pragma once

#include <cstddef>
#include <cstdint>

#include <string>

namespace formulaEngine {

class Token {
public:
  enum TokenType {
    EOE,        // End of expression
    PLUS,       // +
    MINUS,      // -
    STAR,       // *
    SLASH,      // /
    PERCENT,    // %

    NUMBER,     // number

    WHITESPACE, // whitespace

    ILLEGAL,
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
      type()
      {}
};

} // namespase formulaEngine