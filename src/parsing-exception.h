#include <exception>
#include <string>

namespace formulaEngine {
class ParsingException : public std::exception {
  std::string character_;
  size_t beginPosition_;
  size_t endPosition_;

public:
  ParsingException(std::string character, size_t beginPosition, size_t endPosition)
    : character_(character),
      beginPosition_(beginPosition),
      endPosition_(endPosition)
    {}

  std::string character() {
    return character_;
  }

  size_t beginPostion() {
    return beginPosition_;
  }

  size_t endPosition() {
    return endPosition_;
  }

  std::string message() {
    return "Unexpected character " + character_ + " found at position (" + std::to_string(beginPosition_) + "..." + std::to_string(endPosition_) + ").";
  }
};
}