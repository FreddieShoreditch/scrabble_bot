#include "BoardMarker.hpp"

BoardMarker::BoardMarker (void) : m(NONE), c(' ') {}

bool BoardMarker::apply_modifier(Modifier& m) {
  if (this->m != NONE) {
    return false;
  }
  this->m = m;
  return true;
}

bool BoardMarker::set_char(char& c) {
  if (this->c != ' ') {
    return this->c == c;
  }
  this->c = toupper(c);
  return true;
}

char BoardMarker::get_char(void) {
  return this->c;
}

void BoardMarker::print_marker(void) {
  string pre = " ";
  string col = "";
  string post = " ";
  if (this->m != NONE) {
    pre = " \033[";
    post = "\033[0m ";
    switch (this->m) {
      case DOUBLE_L:
        col = "1;43;37m";
        break;
      case DOUBLE_W:
        col = "1;42;37m";
        break;
      case TRIPLE_L:
        col = "1;44;37m";
        break;
      case TRIPLE_W:
        col = "1;41;37m";
        break;
      case NONE:
        cout << "Shouldn't reach this line!" << endl;
    }
  }

  cout << pre << col << this->c << post;
}
