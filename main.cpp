#include "main.hpp"

static bool errors;

int main(int argc, char** argv) {
  options opts;
  int c;

  while ((c = getopt (argc, argv, "b:g:h")) != -1) {
    switch (c) {
      case 'b':
        if (!opts.game_played.empty()) {
          print_error("You cannot set both the board type and the game you're playing. Using game played as priority.");
        } else {
          string opt(optarg);
          opts.board_config = opt;
          if (opt.compare("Scrabble") == 0) {
            opts.board_config = "./board_configs/hasbro_scrabble.json";
          } else if (opt.compare("WordsWFriends") == 0) {
            opts.board_config = "./board_configs/words_with_friends.json";
          }
        }
        break;
      case 'g':
        if (!opts.board_config.empty()) {
          print_error("You cannot set both the board type and the game you're playing. Using board config as priority.");
        } else {
          opts.game_played = optarg;
        }
        break;
      case 'h':
        usage();
        exit(EXIT_SUCCESS);
    }
  }

  if (!check_options(opts)) {
    usage();
  }

  if (!check_file_exists(opts.board_config, true)) {
    exit(EXIT_FAILURE);
  };

  // Print configuration
  if (errors) { cout << endl; }
  cout << "Starting scrabble bot!..." << endl << endl;
  cout << "Board file:\t" << opts.board_config << endl;

  // Generate board and start playing
  Board bd(opts.board_config);

  return 0;

}

void print_error(string err) {
  if (!errors) {
    cout << endl << "Errors:" << endl;
    errors = true;
  }
  cout << "\t" << err << endl;
}

bool check_options(options o) {
  bool valid = true;

  valid &= !o.board_config.empty() || !o.game_played.empty();

  return valid;
}

bool check_file_exists(string s, bool print_err) {
  ifstream file(s);
  bool exists_ = (!file) ? false : true;
  if (!exists_ && print_err) {
    print_error("Config file doesn't exist!");
  }
  return exists_;
}

void usage(void) {
  cout << "Usage:\t./main <args>" << endl << endl;
  cout << "Options:" << endl;
  cout << "\t" << "-b" << "\t:\t" << "Board configuration preset to use, or file to read from";
  cout << " -- Not to be used with '-g'" << endl;
  cout << "\t" << "-g" << "\t:\t" << "Game being played (Scrabble|WordsWFriends)";
  cout << " -- Not to be used with '-b'" << endl;
}
