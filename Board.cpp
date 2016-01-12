#include "Board.hpp"

Board::Board(string& name_, int& width_, int& height_,
  rapidjson::Value& mods, rapidjson::Value& scores)
  : name(name_), width(width_), height(height_), scoring() {
  this->board.resize(width);
  Modifier centre = CENTRE;

  for (size_t i = 0; i < this->board.size(); i++) {
    this->board[i].resize(height);
    for (int j = 0; j < width; j++) {
      this->board[i][j] = new BoardMarker();
      if ((j == ceil(width / 2) || j == floor(width / 2)) &&
          (i == ceil(height / 2) || i == floor(height / 2))) {
            this->board[i][j]->apply_modifier(centre);
          }
    }
  }

  if (!mods["double_l"].IsNull()) {
    Modifier m = DOUBLE_L;
    apply_modifier_array(m, mods["double_l"]);
  }

  if (!mods["triple_l"].IsNull()) {
    Modifier m = TRIPLE_L;
    apply_modifier_array(m, mods["triple_l"]);
  }

  if (!mods["double_w"].IsNull()) {
    Modifier m = DOUBLE_W;
    apply_modifier_array(m, mods["double_w"]);
  }

  if (!mods["triple_w"].IsNull()) {
    Modifier m = TRIPLE_W;
    apply_modifier_array(m, mods["triple_w"]);
  }

  if (!scores.IsNull()) {
    for (char c = 'a'; c <= 'z'; c++) {
      string s({ c, '\0'});
      int score = scores[s.c_str()].GetInt();
      this->scoring.emplace(c, score);
    }
  }
}

void Board::apply_modifier_array(Modifier& m, rapidjson::Value& mod_array) {
  assert(mod_array.IsArray());
  for (rapidjson::SizeType i = 0; i < mod_array.Size(); i++) {
    int x = mod_array[i]["x"].GetInt();
    int y = mod_array[i]["y"].GetInt();
    this->board[x - 1][y - 1]->apply_modifier(m);
  }
}

bool Board::can_set_word(string s, int w, int h, Direction d) {
  // Check the positioning is on the board
  int longitude = DirectionUtils::get_direction_longitude(d);
  int latitude = DirectionUtils::get_direction_latitude(d);

  int w_diff = w + ((s.length() - 1) * longitude);
  int h_diff = h + ((s.length() - 1) * latitude);

  // Ensure all variables lie within the board
  bool w_val = w >= 0 && w < this->width;
  bool w_diff_val = w_diff >= 0 && w_diff < this->width;
  bool h_val = h >= 0 && h < this->height;
  bool h_diff_val = h_diff >= 0 && h_diff < this->height;

  if (!(w_val && w_diff_val && h_val && h_diff_val)) {
    return false;
  }

  // Check that nothing, or the character intended is in place
  for (size_t i = 0; i < s.length(); i++) {
    char current = this->get_char(w + (i * longitude), h + (i * latitude));
    if (current != ' ' && s[i] != current) { return false; }
  }
  return true;
}

bool Board::set_word(string s, int w, int h, Direction d) {
  int longitude = DirectionUtils::get_direction_longitude(d);
  int latitude = DirectionUtils::get_direction_latitude(d);

  if (!this->can_set_word(s, w, h, d)) { return false; }

  for (size_t i = 0; i < s.length(); i++) {
    if (!this->set_char(s[i], w + (i * longitude), h + (i * latitude))) {
      return false;
    }
  }
  return true;
}

bool Board::set_char(char c, int w, int h) {
  if ( w < this->width && h < this->height
    && w >= 0 && h >= 0) {
    return this->board[w][h]->set_char(c);
  }
  return false;
}

string Board::get_word(int w, int h, Direction d) {
  int longitude = DirectionUtils::get_direction_longitude(d);
  int latitude = DirectionUtils::get_direction_latitude(d);

  char c;
  string s = "";
  while ((c = this->get_char(w, h)) != ' ' && Board::valid_position(w, h)) {
    s.append(&c);
    w += longitude;
    h += latitude;
  }
  return s;
}

char Board::get_char(int w, int h) {
  return this->board[w][h]->get_char();
}

int Board::get_width(void) {
  return this->width;
}

int Board::get_height(void) {
  return this->height;
}

void Board::print_board(void) {
  this->print_line_row();
  for (int j = (int) this->board[0].size() - 1; j > -1 ; j--) {
    cout << "|";
    for (size_t i = 0; i < this->board.size(); i++) {
      this->board[i][j]->print_marker();
      cout << "|";
    }
    cout << endl;
    this->print_line_row();
  }
}

void Board::print_line_row(void) {
  string s("+");
  for (size_t i = 0; i < this->board.size(); i++) {
    s.append("----");
  }
  s.erase(s.end() - 1);
  s.append("+");
  cout << s << endl;
}

bool Board::valid_position(int& w, int& h) {
  return (
    w >= 0 && w < this->width &&
    h >= 0 && h < this->height
  );
}

int Board::get_score_for_char(char& c) {
  auto it = this->scoring.find(c);
  if (it != this->scoring.end()) {
    return get<1>(*it);
  } else {
    return -1;
  }
}
