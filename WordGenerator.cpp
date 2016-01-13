#include "WordGenerator.hpp"

WordGenerator::WordGenerator(unordered_set<CharacterInput* >& characters, unordered_set<WordPlay* >& results)
  : input(characters), out(results) {}

void WordGenerator::Generator(void) {
  cout << "Generating word plays..." << endl;
  cout << "Input size:\t" << input.size() << endl;
  cout << "Output size:\t" << out.size() << endl;
}
