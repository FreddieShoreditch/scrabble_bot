#include "Board.hpp"

Board::Board(string& config) {
  ifstream config_file(config);

  // get length of file:
  config_file.seekg (0, config_file.end);
  int length = config_file.tellg();
  config_file.seekg (0, config_file.beg);
  char* config_file_raw = new char[length];

  config_file.read(config_file_raw, length);

  rapidjson::Document d;
  d.Parse(config_file_raw);

  // 3. Stringify the DOM
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  d.Accept(writer);

  // Output {"project":"rapidjson","stars":11}
  cout << buffer.GetString() << endl << endl;
  cout << config_file_raw << endl;
}
