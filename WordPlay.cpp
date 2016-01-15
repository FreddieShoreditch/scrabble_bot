#include "WordPlay.hpp"

WordPlay::WordPlay(string& word, int& w, int& h, Direction d
  , int& score, int blanks)
  : word_(word), w_(w), h_(h), s(score), b(blanks), d_(d) {}

string& WordPlay::get_word(void) {
  return this->word_;
}

int& WordPlay::get_w(void) {
  return this->w_;
}

int& WordPlay::get_h(void) {
  return this->h_;
}

int& WordPlay::get_score(void) {
  return this->s;
}

int& WordPlay::number_blanks(void) {
  return this->b;
}

Direction& WordPlay::get_d(void) {
  return this->d_;
}

bool WordPlay::operator< (WordPlay* that) {
  if (this->s < that->s) {
    return false;
  }
  return false;
}
