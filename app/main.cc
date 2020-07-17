#include <iostream>
#include <string>
#include <memory>

#include "engine.h"

int main(int, char**) {
  std::string input;
  

  // formulaEngine::Lexer lexer(std::make_unique<formulaEngine::Scanner>(input));

  // formulaEngine::Token token;
  // while ((token = lexer.ReadNext()).type != formulaEngine::Token::EOE) {
  //   std::cout << "Found token " << token.value << " (" << token.type << ") at position (" << token.beginPosition << "..." << token.endPosition << ")." << std::endl;
  // }

  while (true) {
    std::getline(std::cin, input);

    if (input == "q") {
      break;
    }

    formulaEngine::Engine engine;
    int result = engine.Evaluate(input);
    std::cout << "RES: " << result << std::endl;
  }

  
}
