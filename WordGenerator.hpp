#ifndef WORDGENERATOR_H

#define WORDGENERATOR_H

#include <iostream>
#include <unordered_set>

// Created libraries
#include "CharacterInput.hpp"
#include "WordPlay.hpp"

using namespace std;

class WordGenerator {

  private:
    unordered_set<CharacterInput* >& input;
    unordered_set<WordPlay* >& out;

  public:
    WordGenerator(unordered_set<CharacterInput* >& characters, unordered_set<WordPlay* >& results);
    void Generator(void);

};

#endif
