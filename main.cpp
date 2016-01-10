#include "main.hpp"

typedef struct {
  string board_config;
  string game_played;
} options;

static bool errors;

int main(int argc, char** argv) {
  cout << "Starting scrabble bot!..." << endl << endl;

  options opts;
  int c;

  while ((c = getopt (argc, argv, "b:g:")) != -1) {
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
    }
  }

  cout << opts.board_config << endl;
  cout << opts.game_played << endl;

  return 0;

}

void print_error(string err) {
  if (!errors) {
    cout << "Errors:" << endl;
    errors = true;
  }
  cout << "\t" << err << endl;
}
