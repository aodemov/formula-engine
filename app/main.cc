#include <iostream>
#include <string>
#include <memory>

#include "lexer.h"

int main(int, char**) {
  std::string input;
  std::getline(std::cin, input);

  formulaEngine::Lexer lexer(std::make_unique<formulaEngine::Scanner>(input));

  formulaEngine::Token token;
  while ((token = lexer.ReadNext()).type != formulaEngine::Token::EOE) {
    std::cout << "Found token " << token.value << " (" << token.type << ") at position (" << token.beginPosition << "..." << token.endPosition << ")." << std::endl;
  }
}
