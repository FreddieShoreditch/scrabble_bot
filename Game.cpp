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

  // Get the wordlist and put it in memory
  this->wordlist = new unordered_set<string >();
  this->get_wordlist(o.language_file);
  if (this->wordlist->empty()) {
    print_error("Wordlist could not be loaded. File used:\t" + o.language_file);
  }

  cout << "Words available:\t" << this->words_available << endl;
  cout << "Players:\t\t" << this->players << endl;
  cout << "Your Go:\t\t" << this->this_player_go << endl;
  cout << endl;

  assert(o.players > 0 && o.this_player_go > 0 && o.this_player_go <= o.players);

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
    int x, y;
    Direction d;

    while (true) {
      string word_regex("[A-Za-z]{0,");
      word_regex.append(to_string(this->tiles_each));
      word_regex.append("}");
      regex validator(word_regex);

      // Get the word
      cout << "Please enter the word (if you type more than 1 word, the second will be ignored):\t";
      cin >> noskipws >> input;
      cin.clear();
      cin.ignore(INT_MAX, '\n');

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

    while (true) {
      regex y_("^[A-Za-z]$");

      // Get the position
      cout << "Please enter the position on the board (e.g. 1 A):\t";
      cin >> input;
      try {
        x = stoi(input);
        if (x <= 0 || x > this->b->get_width()) {
          throw invalid_argument("");
        }
        x -= 1; // Convert from user to program
      } catch (invalid_argument e) {
        cout << "The value " << input << " is not in the range {1,"
             << this->b->get_width() << "}."<< endl;
        continue;
      }

      cin >> input;
      if (!regex_match(input, y_)) {
        continue;
      }
      y = (int) toupper(input[0]) - 'A';

      cin.clear();
      cin.ignore(INT_MAX, '\n');

      if (this->b->valid_position(x, y)) {
        break;
      }
    }

    while (true) {
      // Get the word
      cout << "Please enter the direction (NORTH|EAST|SOUTH|WEST):\t";
      cin >> input;
      cin.clear();
      cin.ignore(INT_MAX, '\n');

      for (auto& c : input) {
        c = toupper(c);
      }

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

    if (can_put_word_on_board(word, x, y, d)) {
      this->b->set_word(word, x, y, d);
      break;
    }

    cout << "Incorrect parameters specified. Please try again!" << endl;
  }
}

void Game::player_go(void) {
  while (true) {
    string input_; // Dummy variable
    vector<char > input;

    // For putting on the Board
    int tiles_available = 0;
    // string word;
    // int x, y;
    // Direction d;

    // Get the number of tiles
    while (true) {
      cout << "How many tiles do you have left? (Between 0 and "
           << to_string(this->tiles_each) << ")\t";
      cin >> input_;
      try {
        tiles_available = stoi(input_);
        if (tiles_available > 0 && tiles_available <= this->tiles_each) {
          break;
        }
      } catch (invalid_argument e) {
        continue;
      }
    }

    // Get the tiles
    cout << "Please enter the tiles you have left, separated by a space:\t";
    char c;
    for (int i = 0; i < tiles_available; i++) {
      cin >> c;
      input.push_back(toupper(c));
    }
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    break;
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
  return it == this->wordlist->end();
}

// Assumes that string input is a valid word.
bool Game::can_put_word_on_board(string& word, int& w, int& h, Direction& d) {
  return true;
}

void Game::get_wordlist(string& filename) {
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
      this->wordlist->insert(word);
    }
  }

  this->words_available = this->wordlist->size();
}
