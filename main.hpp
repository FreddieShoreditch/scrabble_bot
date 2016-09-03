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

    // Must have a board config and player options
    valid &= !this->board_config.empty() || !this->players || !this->this_player_go;

    // Must have a language file / wordlist
    valid &= !this->language_file.empty();

    return valid;
  }
} options;

// Created Libraries
#include "Game.hpp"

void print_error(string err);
void usage(void);
bool check_options(options o);
bool check_file_exists(string s, bool print_err = false);

#endif
