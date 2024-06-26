#include <string>
#include <vector>
#include "tokens.h"
using namespace std;

static const string IDENT_TERMINATOR = ";\n ()[]{}";

bool is_ident_terminator(char ch);
bool valid_ident(string ident);
bool valid_sident(string ident);

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

  Lexer copy();

  void debug(bool show_spaces);

  bool next_token();
  bool next_skip_space();
};

class FakeLexer : public Lexer {
private:
  unsigned int advanced;
public:
  FakeLexer(Lexer * original);
  ~FakeLexer();

  bool next_token();

  void merge(Lexer * lexer);
};
