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

  // The wordlist to use for validating wordplays
  string language_file;

  // Number of players playing and which go you are
  int players;
  int this_player_go;

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
    }

    // Must have players and what player you are
    bool players_valid = !this->players || !this->this_player_go;
    valid &= players_valid;
    if (!players_valid) {
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

bool check_options(options o);
bool check_file_exists(string s, bool print_err = false);

#endif
