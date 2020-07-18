#include <iostream>
#include <string>
#include <memory>

#include "engine.h"
#include "parsing-exception.h"

int main(int, char**) {
  std::string input;

  formulaEngine::Engine engine;

  while (true) {
    std::getline(std::cin, input);

    if (input == "q") {
      break;
    }

    try {
      double result = engine.Evaluate(input);
      std::cout << "RES: " << result << std::endl;
    } catch(formulaEngine::ParsingException& e) {
      std::cout << "ERROR: " << e.message() << std::endl;
    }
    
  }

  
}
