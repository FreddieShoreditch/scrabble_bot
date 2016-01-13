#include "WordPlay.hpp"

WordPlay::WordPlay(string& word, int& w, int& h, Direction d, int& score)
  : word_(word), w_(w), h_(h), s(score), d_(d) {}

int& WordPlay::get_w(void) {
  return this->w_;
}

int& WordPlay::get_h(void) {
  return this->h_;
}

int& WordPlay::get_score(void) {
  return this->s;
}

Direction WordPlay::get_d(void) {
  return this->d_;
}
