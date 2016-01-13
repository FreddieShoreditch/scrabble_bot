#ifndef WORDPLAY_H

#define WORDPLAY_H

#include <string>

#include "Direction.hpp"

using namespace std;

class WordPlay {

  private:
    string word_;
    int w_, h_, s;
    Direction d_;

  public:
    WordPlay(string& word, int& w, int& h, Direction d, int& score);
    int& get_w(void);
    int& get_h(void);
    int& get_score(void);
    Direction get_d(void);

};

#endif
