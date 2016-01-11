#ifndef GAME_H

#define GAME_H

#include <iostream>
#include <sstream>
#include <regex>
#include <unordered_set>
#include <climits>

// Dependencies
#include "submodules/rapidjson/include/rapidjson/document.h"
#include "submodules/rapidjson/include/rapidjson/writer.h"
#include "submodules/rapidjson/include/rapidjson/prettywriter.h"
#include "submodules/rapidjson/include/rapidjson/stringbuffer.h"

#include "main.hpp"
#include "Board.hpp"
#include "Direction.hpp"

using namespace std;

class Game {

  private:
    Board* b;
    int players;
    int this_player_go;
    int tiles_each;
    int tiles_left;
    int words_available;
    unordered_set<string >* wordlist;
    bool is_end(void);
    void player_go(void);
    void opponent_go(void);
    bool valid_word_for_game(string& input);
    bool valid_position_for_game(int& x, int& y);
    bool can_put_word_on_board(string& word, int& w, int& h, Direction& d);
    void get_wordlist(string& file);

  public:
    Game(options o);

};
rapidjson::Document get_config_from_file(string& config);

#endif