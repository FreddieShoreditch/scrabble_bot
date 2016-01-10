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
          opts.board_config = optarg;
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

  if (errors) { cout << endl; }
  cout << "Starting scrabble bot!..." << endl << endl;

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

void usage(void) {
  cout << "Usage:\t./main <args>" << endl << endl;
  cout << "Options:" << endl;
  cout << "\t" << "-b" << "\t:\t" << "Board configuration preset to use, or file to read from";
  cout << " -- Not to be used with '-g'" << endl;
  cout << "\t" << "-g" << "\t:\t" << "Game being played (Scrabble|WordsWFriends)";
  cout << " -- Not to be used with '-b'" << endl;
}
