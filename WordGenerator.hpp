#ifndef WORDGENERATOR_H

#define WORDGENERATOR_H

#include <iostream>
#include <set>
#include <unordered_set>

// Created libraries
#include "CharacterInput.hpp"
#include "WordPlay.hpp"
#include "Board.hpp"

using namespace std;

struct wordplay_compare {
    bool operator() (WordPlay* a, WordPlay* b) const {
      return a->get_score() > b->get_score();
    };
};

class WordGenerator {

  private:
    unordered_set<CharacterInput* >& input;
    set<WordPlay*, wordplay_compare >& out;
    Board& b;
    void generate_at_position(int x, int y);

  public:
    WordGenerator(unordered_set<CharacterInput* >& characters, Board& board, set<WordPlay*, wordplay_compare >& results);
    void Generator(void);

};

#endif
