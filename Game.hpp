#ifndef GAME_H

#define GAME_H

#include <iostream>

// Dependencies
#include "submodules/rapidjson/include/rapidjson/document.h"
#include "submodules/rapidjson/include/rapidjson/writer.h"
#include "submodules/rapidjson/include/rapidjson/prettywriter.h"
#include "submodules/rapidjson/include/rapidjson/stringbuffer.h"

#include "main.hpp"
#include "Board.hpp"

class Game {

  private:
    Board* b;
    int players;
    int this_player_go;

  public:
    Game(options o);

};

rapidjson::Document get_config_from_file(string& config);

#endif
