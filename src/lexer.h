#pragma once

#include <map>

#include "token.h"
#include "scanner.h"
#include "char-predicates.h"

namespace formulaEngine {
class Lexer {
public:
  explicit Lexer(Scanner* scanner)
    : scanner(scanner)
    {}

  Token ReadNext();
private:
  Token::TokenType ReadNumber();
  void SkipWhitespace();

  Token::TokenType ReadSingleToken();

  constexpr Token::TokenType GetOneCharToken(char c) {
    return
      c == '+' ? Token::PLUS :
      c == '-' ? Token::MINUS :
      c == '*' ? Token::STAR :
      c == '/' ? Token::SLASH :
      c == '%' ? Token::PERCENT :
      isDigit(c) ? Token::NUMBER :
      isWhitespace(c) ? Token::WHITESPACE :
      c == Scanner::kEndOfInput ? Token::EOE :
      Token::ILLEGAL;
  }

  Scanner* scanner;
  Token current;
};
}
