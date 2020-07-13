#include "lexer.h"
#include "char-predicates.h"
#include "parsing-exception.h"

namespace formulaEngine {
Token Lexer::ReadNext(){
  // if (scanner->EndOfInput())
  //   return Token(scanner->Position(), scanner->Position(), "", Token::TokenType::EOE);
  
  // SkipWhitespace();

  current.value = "";
  current.type = ReadSingleToken();
  current.endPosition = scanner->Position();

  return current;
}

Token::TokenType Lexer::ReadSingleToken() {
  Token::TokenType token;
  char c;
  
  do {
    current.beginPosition = scanner->Position();

    c = scanner->Peek();
    token = GetOneCharToken(c);

    switch (token) {
      case Token::PLUS:
      case Token::MINUS:
      case Token::STAR:
      case Token::SLASH:
      case Token::PERCENT:
        // One character tokens
        current.value = scanner->Advance();
        return token;

      case Token::WHITESPACE:
        SkipWhitespace();
        continue;

      case Token::NUMBER:
        return ReadNumber();

      case Token::EOE:
        // End of source encountered, return EOE token and do not advance.
        return token;
      
      default:
        // There is only one left
        return Token::ILLEGAL;
    }

  } while (token == Token::WHITESPACE);
  return token;
}

void Lexer::SkipWhitespace(){
  while (isWhitespace(scanner->Peek())) {
    scanner->Advance();
  }
}

Token::TokenType Lexer::ReadNumber() {
  if (!isDigit(scanner->Peek()))
    return Token::ILLEGAL;

  while (isDigit(scanner->Peek())) {
    current.value += scanner->Advance();
  }

  return Token::NUMBER;
}

} // namespace formulaEngine
