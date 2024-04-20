#include "includes/tokens.h"
#include <cctype>

inline bool is_whitespace(char ch) {
  return WHITESPACES.find(ch) != string::npos;
}
inline bool is_linebreak(char ch) {
  return LINEBREAKS.find(ch) != string::npos;
}
// must start with a alphabetical
bool valid_ident(string ident) {
  if (ident == "") return false;
  if (!isalpha(ident[0])) return false;
  for (int i = 1; i < ident.length(); i++) {
    if (is_whitespace(ident[i])) return false;
  }
  return true;
}

Token::Token(TokenType type, string value) {
  this->type = type;
  this->value = value;
}
Token::Token(string value) {
  this->type = VALUE_TOKEN_TABLE.at(value);
  this->value = value;
}

Token::~Token() {}

RawSource::RawSource(string source) {
  this->source = source;
  this->cursor = Cursor();
  this->lookahead = '\0';
  this->is_started = false;
}
RawSource::~RawSource() {}

bool RawSource::finished() {
  return this->source.length() <= this->cursor.index;
}

void RawSource::advance() {
  if (this->finished()) return;
  if (!this->is_started) {
    this->is_started = true;
    this->lookahead = this->source[this->cursor.index];

    return;
  }

  this->cursor.index += 1;
  this->lookahead = this->source[cursor.index];

  if (is_linebreak(this->lookahead)) {
    this->cursor.row += 1;
    this->cursor.col = 0;
  } else {
    this->cursor.col += 1;
  }
}

void RawSource::advance_by(int n) {
  for (int i = 0; i <= n; i++) {
    this->advance();
  }
}

RawSource RawSource::peekable() {
  RawSource tmp(this->source.substr(this->cursor.index));
  tmp.advance();

  return tmp;
}

bool RawSource::expect(string str) {
  RawSource fake = this->peekable();

  for (char c : str) {
    if (c != fake.lookahead) {
      return false;
    }
    fake.advance();
  }

  this->advance_by(str.length());
  return true;
}