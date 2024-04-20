#include <string>
#include <vector>
#include "tokens.h"
using namespace std;

// Actually any token that already have its definition in token table is terminator.
static const string IDENT_TERMINATOR = ";\n ()[]{}^+-";

bool is_ident_terminator(char ch);
bool valid_ident(string ident);

class Lexer {
public:
  RawSource source;
  Token current;
  vector<Token> tokens;

  Lexer(RawSource source);
  ~Lexer();

  // Remember: NO AMBIGUITIES ON GRAMMAR
  // All these functions return true for success and false for failure
  bool test_in_token_table(string str);
  bool test_token_table();
  bool test_ident();
  bool test_string();
  bool test_decimal();
  bool test_whitespace();

  void debug(bool show_spaces);

  bool next_token();
};
