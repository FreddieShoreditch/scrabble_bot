#ifndef BOARD_H

#define BOARD_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

// Dependencies
#include "submodules/rapidjson/include/rapidjson/document.h"
#include "submodules/rapidjson/include/rapidjson/writer.h"
#include "submodules/rapidjson/include/rapidjson/stringbuffer.h"

using namespace std;

// Board has multiple configurations. The configuration is loaded
// and used to generate a board using this class
class Board {

  private:
    vector<vector<int> > board;

  public:
    Board(string& config);

};

#endif
