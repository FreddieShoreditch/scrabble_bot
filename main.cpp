#include "main.hpp"

static bool errors;

int main(int argc, char** argv) {
  options opts;
  int c;

  // Set defaults
  opts.language_file = "./submodules/wordlists_en_mozilla/en_GB (Marco Pinto) - 2.32 - 2016-01-01/wordlist_marcoagpinto_20160101_153347w.txt";

  while ((c = getopt (argc, argv, "b:g:o:hl:")) != -1) {
    string opt(optarg);
    switch (c) {
      case 'b':
        opts.board_config = opt;
        if (opt.compare("Scrabble") == 0) {
          opts.board_config = "./board_configs/hasbro_scrabble.json";
        } else if (opt.compare("WordsWFriends") == 0) {
          opts.board_config = "./board_configs/words_with_friends.json";
        }
        break;
      case 'p':
        opts.players = stoi(opt);
        break;
      case 'o':
        opts.this_player_go = stoi(opt);
        break;
      case 'h':
        usage();
        exit(EXIT_SUCCESS);
        break;
      case 'l':
        if (opt.compare("en_GB") == 0 || opt.compare("en") == 0 ||
            opt.compare("English") == 0 || opt.compare("english") == 0) {
          continue;
        } else {
          print_error("Language given is not known. Please try again.");
        }
    }
  }

  if (!check_options(opts)) {
    usage();
  }

  if (!check_file_exists(opts.board_config, true)) {
    exit(EXIT_FAILURE);
  };

  // Print configuration
  if (errors) { exit(EXIT_FAILURE); }

  // Continue with game
  cout << "Starting scrabble bot!..." << endl << endl;
  cout << "Board file:\t" << opts.board_config << endl;

  new Game(opts);

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

  valid &= !o.board_config.empty() || !o.players || !o.this_player_go;

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
