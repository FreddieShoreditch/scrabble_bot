#include "Board.hpp"

Board::Board(string& name_, int& width_, int& height_, rapidjson::Value& mods)
  : name(name_), width(width_), height(height_) {
  this->board.resize(height);
  for (size_t i = 0; i < this->board.size(); i++) {
    this->board[i].resize(width);
    for (int j = 0; j < width; j++) {
      this->board[i][j] = new BoardMarker();
    }
  }

}
