#pragma once

#include <map>
#include <memory>

#include "token.h"
#include "scanner.h"
#include "char-predicates.h"

namespace formulaEngine {
class Lexer {
public:
  explicit Lexer(std::unique_ptr<Scanner> scanner)
    : scanner(std::move(scanner))
    {}

  Token ReadNext();
  Token Peek();
private:
  Token::TokenType ReadSingleToken();
  Token::TokenType ReadNumber();
  void ReadNextToken();

  void SkipWhitespace();
  bool ReadDigits();

  constexpr Token::TokenType GetOneCharToken(char c) {
    return
      c == '+' ? Token::PLUS :
      c == '-' ? Token::MINUS :
      c == '*' ? Token::STAR :
      c == '/' ? Token::SLASH :
      c == '%' ? Token::PERCENT :
      isDecimalPoint(c) ? Token::POINT :
      isDigit(c) ? Token::NUMBER :
      isWhitespace(c) ? Token::WHITESPACE :
      c == Scanner::kEndOfInput ? Token::EOE :
      Token::ILLEGAL;
  }

  std::unique_ptr<Scanner> scanner;
  Token current;
  Token next;
};
}
