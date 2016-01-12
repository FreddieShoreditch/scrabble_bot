#include "CharacterInput.hpp"

CharacterInput::CharacterInput(char& c_, int& s)
  : c(toupper(c_)), score(s) {}

char& CharacterInput::get_char(void) {
  return this->c;
}

int& CharacterInput::get_score(void) {
  return this->score;
}
