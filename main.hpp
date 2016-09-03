#ifndef MAIN_H

#define MAIN_H

#include <iostream>
#include <fstream>

// As per getopt example
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

void print_error(string err);
void usage(void);

typedef struct {
  // Configuration to use for the game, in JSON
  string board_config;
  bool set_board_config;

  // The wordlist to use for validating wordplays
  string language_file;
  bool set_language_file;

  // Number of players playing and which go you are
  int players;
  int this_player_go;
  bool set_players;

  // Initialisation of options for defaults
  void init(void) {
    this->players = 2;
    this->this_player_go = 1;
    this->language_file = "./submodules/wordlists_en_mozilla/en_GB (Marco Pinto) - 2.32 - 2016-01-01/wordlist_marcoagpinto_20160101_153347w.txt";
  }

  // Validate options
  bool validate(void) {
    bool valid = true;

    // Must have a board config
    bool board_config_valid = !this->board_config.empty();
    valid &= board_config_valid;
    if (!board_config_valid) {
      print_error("No board config set. Please set a board configuration.");
      usage();
    } else {
      if (this->board_config.compare("Scrabble") == 0) {
        this->board_config = "./board_configs/hasbro_scrabble.json";
      } else if (this->board_config.compare("WordsWFriends") == 0) {
        this->board_config = "./board_configs/words_with_friends.json";
      }

      ifstream file(this->board_config);
      if (!file) {
        valid = false;
        print_error("Config file doesn't exist at " + this->board_config);
      }
    }

    // Must have players and what player you are
    bool players_valid =  this->players != -1 &&
                          this->this_player_go > 0 &&
                          this->this_player_go <= this->players;
    valid &= players_valid;
    if (!players_valid) {
      print_error("Players:\t" + to_string(this->players));
      print_error("Player Go:\t" + to_string(this->this_player_go));
      print_error("You must set number of players and which player you are.");
      usage();
    }

    // Must have a language file / wordlist
    bool language_file_valid = !this->language_file.empty();
    valid &= language_file_valid;
    if (!language_file_valid) {
      print_error("No wordlist set. You must set a wordlist to use.");
      usage();
    }

    return valid;
  }
} options;

// Created Libraries
#include "Game.hpp"

#endif
