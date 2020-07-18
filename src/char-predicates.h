#pragma once

#include <cstddef>
#include <cstdint>

namespace formulaEngine {
inline bool isWhitespace(char c) {
  return (c ==  ' ') || (c == '\n') ||
         (c == '\r') || (c == '\t') ||
         (c == '\b') || (c == '\v') ||
         (c == '\f');
}

inline bool isLetter(char c) {
   return (('a' <= c) && (c <= 'z')) ||
          (('A' <= c) && (c <= 'Z'));
}

inline bool isDigit(char c) {
  return ('0' <= c) && (c <= '9');
}

inline bool isLetterOrDigit(char c) {
  return isLetter(c) || isDigit(c);
}

inline bool isDecimalPoint(char c) {
  return c == '.';
}

inline bool isExponentialNotation(char c) {
  return c == 'e' || c == 'E';
}

inline bool isSignOperator(char c) {
  return c == '-' || c == '+';
}
}
