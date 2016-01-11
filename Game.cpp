#include "Game.hpp"

Game::Game(options o) : players(o.players), this_player_go(o.this_player_go) {
  // Generate board and start playing
  rapidjson::Document d = get_config_from_file(o.board_config);
  string board_name(d["board_name"].GetString());
  int width = d["board_width"].GetInt();
  int height = d["board_height"].GetInt();
  rapidjson::Value& mods(d["modifiers"]);
  rapidjson::Value& scores(d["scores"]);
  this->b = new Board(board_name, width, height, mods, scores);

  assert(o.players > 0 &&
    o.this_player_go > 0 && o.this_player_go <= o.players
  );

  cout << "Players:\t" << this->players << endl;
  cout << "Your Go:\t" << this->this_player_go << endl;
  cout << "Board:\t" << endl;
  this->b->print_board();
}

rapidjson::Document get_config_from_file(string& config) {
  ifstream config_file(config);

  // get length of file:
  config_file.seekg (0, config_file.end);
  int length = config_file.tellg();
  config_file.seekg (0, config_file.beg);
  char* config_file_raw = new char[length];

  config_file.read(config_file_raw, length);

  rapidjson::Document d;
  d.Parse(config_file_raw);

  return d;
}
