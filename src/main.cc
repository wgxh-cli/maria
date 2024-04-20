#include <cstring>
#include <ios>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include "includes/lexer.h"
using namespace std;

int main(int argc, char* argv[]) {
  using namespace filesystem;

  if (argc <= 1) return 1;
  string file_path = argv[1];
  path src = file_path;
  bool debug_show_space = false;
  if (argc >= 3 && strcmp(argv[2], "-s") == 0) {
    debug_show_space = true;
  }

  ifstream in;
  stringstream buf;
  string content;

  in.open(src, ios::in);
  buf << in.rdbuf();
  content = buf.str();

  RawSource source(content);
  Lexer lexer(source);
  RawSource fake = lexer.source.peekable();
  lexer.source.advance();

  while (!lexer.source.finished()) {
    if (!lexer.next_token()) {
      cerr << "Failed at: " << lexer.source.cursor.row << ":" << lexer.source.cursor.col << endl;

      break;
    }
  }
  lexer.debug(debug_show_space);

  return 0;
}
