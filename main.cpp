#include "main.hpp"

static bool errors;

int main(int argc, char** argv) {
  options opts;
  opts.init();
  int c;

  while ((c = getopt (argc, argv, "b:o:p:l:h")) != -1) {
    string opt(optarg);
    switch (c) {
      case 'b':
        opts.board_config = opt;
        if (opt.compare("Scrabble") == 0) {
          opts.board_config = "./board_configs/hasbro_scrabble.json";
        } else if (opt.compare("WordsWFriends") == 0) {
          opts.board_config = "./board_configs/words_with_friends.json";
        }
        opts.set_board_config = true;
        break;
      case 'p':
        opts.players = stoi(opt);
        opts.set_players = true;
        break;
      case 'o':
        opts.this_player_go = stoi(opt);
        opts.set_players = true;
        break;
      case 'h':
        usage();
        exit(EXIT_SUCCESS);
        break;
      case 'l':
        if (opt.compare("en_GB") == 0 || opt.compare("en") == 0 ||
            opt.compare("English") == 0 || opt.compare("english") == 0) {
          // Default is English
          continue;
          opts.set_language_file = true;
        } else {
          print_error("Language given is not known. Please try again.");
        }
    }
  }

  if (!opts.validate()) { exit(EXIT_FAILURE); }

  // Continue with game
  cout << "Starting scrabble bot!..." << endl << endl;

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

void usage(void) {
  cout << "Usage:\t./main <args>" << endl << endl;
  cout << "Options:" << endl;
  cout << "\t" << "-b" << "\t:\t" << "Board configuration preset to use, or file to read from";
  cout << " -- Not to be used with '-g'" << endl;
  cout << "\t" << "-g" << "\t:\t" << "Game being played (Scrabble|WordsWFriends)";
  cout << " -- Not to be used with '-b'" << endl;
}
