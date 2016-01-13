#ifndef WORDGENERATOR_H

#define WORDGENERATOR_H

#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>

// Created libraries
#include "CharacterInput.hpp"
#include "WordPlay.hpp"

using namespace std;

class WordGenerator {

  private:
    unordered_set<CharacterInput* >& input;
    vector<WordPlay* >& out;

  public:
    WordGenerator(unordered_set<CharacterInput* >& characters, vector<WordPlay* >& results);
    void Generator(void);

};

#endif
