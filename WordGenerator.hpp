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
    unordered_set<WordPlay* >* input_perms;
    priority_queue<WordPlay* >& out;
    void CalculatePermutations(void);

  public:
    WordGenerator(unordered_set<CharacterInput* >& characters, priority_queue<WordPlay* >& results);
    void Generator(void);

};

#endif
