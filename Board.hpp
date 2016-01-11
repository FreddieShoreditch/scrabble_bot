#ifndef BOARD_H

#define BOARD_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

// Dependencies
#include "submodules/rapidjson/include/rapidjson/document.h"
#include "submodules/rapidjson/include/rapidjson/writer.h"
#include "submodules/rapidjson/include/rapidjson/prettywriter.h"
#include "submodules/rapidjson/include/rapidjson/stringbuffer.h"

// Created libraries
#include "BoardMarker.hpp"
#include "Direction.hpp"
#include "Modifier.hpp"

using namespace std;

// Board has multiple configurations. The configuration is loaded
// and used to generate a board using this class
class Board {

  private:
    void apply_modifier_array(Modifier& m, rapidjson::Value& mod_array);
    bool valid_position(int& w, int& h);
    bool set_char(char c, int w, int h);
    char get_char(int w, int h);
    vector<vector<BoardMarker*> > board;
    string name;
    int width;
    int height;

  public:
    Board(string& name, int& width, int& height, rapidjson::Value& mods);
    void print_board(Board& b);
    bool set_word(string s, int w, int h, Direction d);
    string get_word(int w, int h, Direction d);

};

#endif
