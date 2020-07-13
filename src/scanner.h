#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

namespace formulaEngine {
class Scanner {
  public:
    static constexpr char kEndOfInput = static_cast<char>(-1);

    explicit Scanner(std::string buffer)
      : bufferStart(buffer.begin()),
        bufferEnd(buffer.end()),
        bufferPosition(bufferStart)
        {}

    inline size_t Position() const {
      return bufferPosition - bufferStart;
    }

    inline bool EndOfInput() const {
      return bufferPosition >= bufferEnd;
    }

    // Returns the UTF-16 character at current position.
    // If there are no more characters in the buffer returns kEndOfInput.
    inline char Peek() {
      if (!EndOfInput()) {
        return *bufferPosition;
      } else {
        return kEndOfInput;
      }
    }

    // Returns and then advances the UTF-16 character at current position.
    // If there are no more characters in the buffer returns kEndOfInput.
    inline char Advance() {
      char result = Peek();
      bufferPosition++;
      return result;
    }

  protected:
    const std::string::iterator bufferStart;
    const std::string::iterator bufferEnd;
    std::string::iterator bufferPosition;
};
}