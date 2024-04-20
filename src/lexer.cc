#include "includes/lexer.h"
using namespace std;

Lexer::Lexer(RawSource source) : source(source), current(Token(EMPTY, "")) {}
Lexer::~Lexer() {}

bool Lexer::test_token_table(string str) {
  if (VALUE_TOKEN_TABLE.find(str) != VALUE_TOKEN_TABLE.end() && this->source.expect(str)) {
    this->current = Token(str);

    return true;
  } else {
    return false;
  }
}
bool Lexer::test_ident() {
  RawSource fake = this->source.peekable();
  string ident = "";
  while (!fake.finished()) {
    if (!valid_ident(ident)) break;
    if (is_whitespace(fake.lookahead)) {
      this->source.advance_by(ident.length());
      this->current = Token(IDENT, ident);

      return true;
    } else {
      ident.push_back(fake.lookahead);
      fake.advance();

      continue;
    }
  }
  return false;
}
bool Lexer::next_token() {
  for (const auto [key, value] : TOKEN_VALUE_TABLE) {
    if (!this->test_token_table(key))  {}
  }
}
