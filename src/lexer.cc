#include "lexer.h"
#include "char-predicates.h"
#include "parsing-exception.h"

namespace formulaEngine {
Token Lexer::ReadNext(){
  if (next.type == Token::UNINITIALIZED) {
    ReadNextToken();
  }

  current = next;
  ReadNextToken();

  return current;
}

Token Lexer::Peek(){
  if (next.type == Token::UNINITIALIZED) {
    ReadNextToken();
  }

  return next;
}

void Lexer::ReadNextToken() {
    next.value = "";
    next.type = ReadSingleToken();
    next.endPosition = scanner->Position();
    if (next.type == Token::ILLEGAL)
      throw ParsingException(next.value, next.beginPosition, next.endPosition);
}

Token::TokenType Lexer::ReadSingleToken() {
  Token::TokenType token;
  char c;
  
  do {
    next.beginPosition = scanner->Position();

    c = scanner->Peek();
    token = GetOneCharToken(c);

    switch (token) {
      case Token::PLUS:
      case Token::MINUS:
      case Token::STAR:
      case Token::SLASH:
      case Token::PERCENT:
      case Token::LPAREN:
      case Token::RPAREN:
      case Token::EXCL:
        // One character tokens
        next.value = scanner->Advance();
        return token;

      case Token::WHITESPACE:
        SkipWhitespace();
        continue;

      case Token::NUMBER:
      case Token::POINT:
        return ReadNumber();

      case Token::EOE:
        // End of source encountered, return EOE token and do not advance.
        next.value = "EOE";
        return token;
      
      default:
        // There is only one left
        next.value = scanner->Peek();
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
  bool hasDigitsBeforePoint = false;
  bool hasDecimalPoint = false;
  bool hasDigitsAfterPoint = false;
  bool hasExponentialNotation = false;

  hasDigitsBeforePoint = ReadDigits();

  if (isDecimalPoint(scanner->Peek())) {
    hasDecimalPoint = true;
    next.value += scanner->Advance();

    hasDigitsAfterPoint = ReadDigits();
  }

  if (!hasDigitsBeforePoint && !hasDigitsAfterPoint) {
      return Token::ILLEGAL;
    }

  if (isExponentialNotation(scanner->Peek())) {
    hasExponentialNotation = true;

    next.value += scanner->Advance();

    if (isSignOperator(scanner->Peek())) {
      next.value += scanner->Advance();
    }

    if (!isDigit(scanner->Peek())) {
      return Token::ILLEGAL;
    }

    ReadDigits();
  }
  
  return Token::NUMBER;
}

bool Lexer::ReadDigits() {
  bool read = false;
  while (isDigit(scanner->Peek())) {
    read = true;
    next.value += scanner->Advance();
  }

  return read;
}

} // namespace formulaEngine
