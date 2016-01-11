#ifndef BOARDMARKER_H

#define BOARDMARKER_H

#include <iostream>

// Created libraries
#include "Modifier.hpp"

using namespace std;

class BoardMarker {

  private:
    Modifier m;
    char c;

  public:
    BoardMarker(void);
    bool apply_modifier(Modifier& m);
    void print_marker(void);
    bool set_char(char& c);
    char get_char(void);

};

#endif
