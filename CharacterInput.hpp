#ifndef CHARACTERINPUT_H

#define CHARACTERINPUT_H

#include <ctype.h>

using namespace std;

class CharacterInput {

  private:
    char c_;

  public:
    CharacterInput(char& c);
    char& get_char(void);

};

#endif
