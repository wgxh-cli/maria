#include <string>
#include "tokens.h"
using namespace std;

class Lexer {
public:
  RawSource source;
  Token current;

  Lexer(RawSource source);
  ~Lexer();

  bool test_token_table(string str);
  bool test_ident();

  bool next_token();
};
