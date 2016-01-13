#include "WordGenerator.hpp"

WordGenerator::WordGenerator(unordered_set<CharacterInput* >& characters, vector<WordPlay* >& results)
  : input(characters), out(results) {}

void WordGenerator::Generator(void) {
  cout << "Generating word plays..." << endl;

  WordPlay* wp;
  string s = "-";
  int w = -1;
  int h = -1;
  Direction d = NORTH;
  int score = 0;

  // Always insert the possibility of passing.
  wp = new WordPlay(s, w, h, d, score);
  this->out.push_back(wp);

  cout << "Number of tiles:\t" << this->input.size() << endl;
  cout << "Number of possible WordPlays:\t" << this->out.size() << endl << endl;
}
