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
  string board_config;
  string game_played;
  string language_file;
  int players;
  int this_player_go;

  void init(void) {
    this->players = 2;
    this->this_player_go = 1;
    this->language_file = "./submodules/wordlists_en_mozilla/en_GB (Marco Pinto) - 2.32 - 2016-01-01/wordlist_marcoagpinto_20160101_153347w.txt";
  }
} options;

// Created Libraries
#include "Game.hpp"

void print_error(string err);
void usage(void);
bool check_options(options o);
bool check_file_exists(string s, bool print_err = false);

#endif
