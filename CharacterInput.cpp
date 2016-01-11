#include "CharacterInput.hpp"

CharacterInput::CharacterInput(char& c) : c_(c) {}

char& CharacterInput::get_char(void) {
  return this->c_;
}
