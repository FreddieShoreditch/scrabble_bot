#include "Game.hpp"

Game::Game(options o) : players(o.players), this_player_go(o.this_player_go) {
  this->generate_board(o.board_config);

  // Get the wordlist and put it in memory
  this->wordlist = new unordered_set<string >();
  this->get_wordlist(o.language_file, *(this->wordlist));
  if (this->wordlist->empty()) {
    print_error("Wordlist could not be loaded. File used:\t" + o.language_file);
  }

  cout << "Words available:\t" << this->words_available << endl;
  cout << "Players:\t\t" << this->players << endl;
  cout << "Your Go:\t\t" << this->this_player_go << endl;
  cout << endl;

  assert(o.players > 0 && o.this_player_go > 0 && o.this_player_go <= o.players);

  // Game logic
  int go = 0;
  while (!this->is_end()) {
    int player_turn = go % o.players;
    if (player_turn == o.this_player_go - 1) {
      this->b->print_board();
      cout << "Your go!" << endl;
      this->player_go();
    } else {
      this->b->print_board();
      cout << "Opponent's go:\tPlayer" << (player_turn + 1) << endl;
      this->opponent_go();
    }
    go++;
  }
  this->b->print_board();
  cout << "This is the final board!" << endl;
}

void Game::generate_board(string& input) {
  // Generate board and start playing
  rapidjson::Document d = get_config_from_file(input);
  string board_name(d["board_name"].GetString());
  int width = d["board_width"].GetInt();
  int height = d["board_height"].GetInt();
  rapidjson::Value& mods(d["modifiers"]);
  rapidjson::Value& scores(d["scores"]);
  this->b = new Board(board_name, width, height, mods, scores);

  // Get other details (for later implementation)
  if (d.HasMember("tiles") &&
      d["tiles"].HasMember("each") &&
      d["tiles"].HasMember("total")) {
    this->tiles_each = d["tiles"]["each"].GetInt();
    this->tiles_left = d["tiles"]["total"].GetInt();
  } else {
    this->tiles_each = 7;
    this->tiles_left = 100;
  }
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

bool Game::is_end(void) {
  return this->tiles_left == 0;
}

void Game::opponent_go(void) {
  while (true) {
    string input;

    // For putting on the Board
    string word;
    int x = -1, y = -1;
    Direction d;

    while (true) {
      string word_regex("[A-Za-z]{0,");
      word_regex.append(to_string(this->tiles_each));
      word_regex.append("}");
      regex validator(word_regex);

      // Get the word
      cout << "Please enter the word (if you type more than 1 word, the second will be ignored):\t";
      cin >> input;

      if (input.compare("") == 0) {
        cout << "The opponent passed!" << endl;
        return;
      }

      if (regex_match(input, validator) && valid_word_for_game(input)) {
        word = input;
        break;
      }

      cout << "The word you entered was invalid. Please try again." << endl;
    }

    while (!this->b->valid_position(x, y)) {
      regex y_("^[A-Za-z]$");

      // Get the position
      cout << "Please enter the position on the board (e.g. 1 A):\t";
      cin >> input;
      try {
        x = stoi(input);
        if (x <= 0 || x > this->b->get_width()) {
          throw invalid_argument("X not in range");
        }
        x -= 1; // Convert from user to program
      } catch (invalid_argument e) {
        cout << "The value " << input << " is not in the range {1,"
             << this->b->get_width() << "}."<< endl;
        continue;
      }

      cin >> input;
      cout << input << endl;
      if (!regex_match(input, y_)) {
        continue;
      }
      y = (int) toupper(input[0]) - 'A';
    }

    while (true) {
      // Get the word
      cout << "Please enter the direction ( NORTH | EAST | SOUTH | WEST ):\t";
      cin >> input;
      for (auto& c : input) { c = toupper(c); }

      if (input.compare("NORTH") == 0) {
        d = NORTH; break;
      } else if (input.compare("EAST") == 0) {
        d = EAST; break;
      } else if (input.compare("SOUTH") == 0) {
        d = SOUTH; break;
      } else if (input.compare("WEST") == 0) {
        d = WEST; break;
      }

      cout << "Incorrect direction. Please try again!" << endl;
    }

    if (this->b->can_set_word(word, x, y, d)) {
      this->b->set_word(word, x, y, d);
      break;
    }

    cout << "Cannot put word on the board with the given parameters specified. "
         << "Please try again!" << endl;
  }
}

void Game::player_go(void) {
  while (true) {
    string input_; // Dummy variable
    unordered_set<CharacterInput* > input;
    input.clear(); // Safety

    // For putting on the Board
    int tiles_available = 0;

    // Get the number of tiles
    while (true) {
      cout << "How many tiles do you have left? (Between 0 and "
           << to_string(this->tiles_each) << ")\t";
      cin >> input_;
      try {
        tiles_available = stoi(input_);
        if (tiles_available >= 0 && tiles_available <= this->tiles_each) {
          break;
        }
      } catch (invalid_argument e) {
        continue;
      }
    }

    // Get the tiles
    if (tiles_available > 0) {
      cout << "Please enter the tiles you have left, separated by a space (use '-' for blank):\t";
      char c;
      CharacterInput* ci;
      for (int i = 0; i < tiles_available; i++) {
        while (c < 'A' && c > 'Z' && c != '-') {
          cin >> c;
        }
        int char_score = (c != '-') ? this->b->get_score_for_char(c) : 0;
        ci = new CharacterInput(c, char_score);
        input.insert(ci);
      }
    }

    unordered_set<WordPlay* >* words = new unordered_set<WordPlay* >();
    WordGenerator wgen(input, *words);
    wgen.Generator();

    string res;
    bool cancel = false;
    for (auto& wp : *words) {
      string& s = wp->get_word();
      int& w = wp->get_w();
      int& h = wp->get_h();
      Direction& d = wp->get_d();

      if (!this->b->can_set_word(s, w, h, d)) {
        cout << "Only move is to pass! Passing go!" << endl;
        return;
      } else {
        bool choose = false;
        while (!choose && res.compare("n") != 0) {
          string res;
          cout << "Would you like to play the word \"" << s
               << "\" at position (" << to_string(w + 1)
               << ", " << char(h + 'A') << ") (Score: "
               << wp->get_score() << ") [Y/n/c]:\t";
          cin >> res;
          cancel = res.compare("c") == 0;
          choose = res.compare("Y") == 0 || cancel;
        }

        if (cancel) { break; }

        if (choose) {
          this->b->set_word(s, w, h, d);
          return;
        }
      }
    }
  }
}

// Checks the string against the dictionary
bool Game::valid_word_for_game(string& input) {
  // Make input UPPERCASE
  for (char& c : input) { c = toupper(c); }

  // Checks for whitespace and non-alphas
  regex e("^[A-Z]*$");
  if (!regex_match(input, e)) { return false; }

  // Checks for word in dictionary
  auto it = this->wordlist->find(input);
  return it != this->wordlist->end();
}

void Game::get_wordlist(string& filename, unordered_set<string >& set_) {
  ifstream file(filename);
  string word;
  regex e("^[A-Za-z]*$");

  while (!file.eof()) {
    getline(file, word);

    // Remove \r and \n from word
    int index, last_r, last_n;
    last_r = word.find_last_of('\r');
    if (last_r < 0) { last_r = INT_MAX; }
    last_n = word.find_last_of('\n');
    if (last_n < 0) { last_n = INT_MAX; }

    index = (last_r < last_n) ? last_r : last_n;
    if ((size_t) index > word.size()) { index = word.size(); }

    word = word.substr(0, index);

    if (regex_match(word, e)) {
      set_.insert(word);
    }
  }

  this->words_available = set_.size();
}
