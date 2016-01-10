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
} options;

void print_error(string err);
void usage(void);
bool check_options(options o);

#endif
