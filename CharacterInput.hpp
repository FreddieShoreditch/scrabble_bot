#ifndef CHARACTERINPUT_H

#define CHARACTERINPUT_H

#include <ctype.h>

class CharacterInput {

  private:
    char c;
    int score;

  public:
    CharacterInput(char& c_, int& s);
    char& get_char(void);
    int& get_score(void);

};

#endif
