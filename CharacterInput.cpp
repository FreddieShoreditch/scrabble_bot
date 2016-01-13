#include "CharacterInput.hpp"

CharacterInput::CharacterInput(char& c_, int& s)
  : c(toupper(c_)), score(s), blank(c_ == '-') {}

char& CharacterInput::get_char(void) {
  return this->c;
}

int& CharacterInput::get_score(void) {
  return this->score;
}

bool& CharacterInput::is_blank(void) {
  return this->blank;
}
