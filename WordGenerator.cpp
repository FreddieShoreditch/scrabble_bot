#include "WordGenerator.hpp"

// Intended to generate all possible WordPlays at any given position

WordGenerator::WordGenerator(unordered_set<CharacterInput* >& characters, Board& board, set<WordPlay*, wordplay_compare >& results)
  : input(characters), out(results), b(board) {}

void WordGenerator::Generator(void) {
  WordPlay* wp;
  string s = "-";
  int w = -1;
  int h = -1;
  Direction d = NORTH;
  int score = 0;

  do {
    wp = new WordPlay(s, w, h, d, score);
    this->out.insert(wp);
  } while (false);
}

void generate_at_position(int x, int y) {
  
}
