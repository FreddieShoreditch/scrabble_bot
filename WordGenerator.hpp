#ifndef WORDGENERATOR_H

#define WORDGENERATOR_H

#include <vector>
#include <unordered_set>

// Created libraries
#include "CharacterInput.hpp"

using namespace std;

class WordGenerator {

  public:
    static void Generator(vector<CharacterInput > characters, unordered_set<WordPlay > results);

};

#endif
