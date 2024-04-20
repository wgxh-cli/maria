#include <iostream>
#include "includes/lexer.h"
using namespace std;

int main() {
  RawSource source("<hello world");
  Lexer lexer(source);
  RawSource fake = lexer.source.peekable();
  lexer.source.advance();

  cout << lexer.test_ident() << endl;
  cout << lexer.current.value << endl;

  return 0;
}
