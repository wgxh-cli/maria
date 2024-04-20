#include <iostream>
#include <cctype>
#include "includes/utils.h"
#include "includes/lexer.h"

using namespace std;

Lexer::Lexer(RawSource source) : source(source), current(Token(EMPTY, "")) {}
Lexer::~Lexer() {}

bool Lexer::test_in_token_table(string str) {
  if (VALUE_TOKEN_TABLE.find(str) != VALUE_TOKEN_TABLE.end() && this->source.expect(str)) {
    this->current = Token(str);

    return true;
  } else {
    return false;
  }
}

bool is_ident_terminator(char ch) {
  return IDENT_TERMINATOR.find(ch) != string::npos;
}

bool valid_ident(string ident) {
  if (ident == "") return false;
  if (!isalpha(ident[0])) return false;
  for (int i = 1; i < ident.length(); i++) {
    if (
      IDENT_TERMINATOR.find(ident[i]) != string::npos ||
      is_whitespace(ident[i])
    ) return false;
  }

  return true;
}

bool Lexer::test_ident() {
  RawSource fake = this->source.peekable();
  string ident = "";
  while (!fake.finished()) {
    if (is_ident_terminator(fake.lookahead)) {
      break;
    } else {
      ident.push_back(fake.lookahead);
    }
    fake.advance();
  }
  if (valid_ident(ident)) {
    this->current = Token(IDENT, ident);
    this->source.advance_by(ident.length());

    return true;
  } else {
    return false;
  }
}

bool Lexer::test_string() {
  RawSource fake = this->source.peekable();
  if (fake.lookahead != '"') return false;
  // Advance '"'
  fake.advance();
  string content = "";
  while (!fake.finished()) {
    if (fake.lookahead == '"') {
      if (content != "") {
        this->current = Token(STRING, content);
        this->source.advance_by(content.length() + 2);

        return true;
      }
    } else {
      content.push_back(fake.lookahead);
    }
    fake.advance();
  }
  return false;
}

bool Lexer::test_decimal() {
  RawSource fake = this->source.peekable();
  string res = "";
  bool has_dot = false;

  while (!fake.finished()) {
    if (isdigit(fake.lookahead) || fake.lookahead == '.') {
      res.push_back(fake.lookahead);
      fake.advance();

      if (fake.lookahead == '.') {
        if (has_dot) {
          return false;
        } else {
          has_dot = true;
        }
      }
    } else {
      break;
    }
  }

  if (res != "") {
    this->source.advance_by(res.length());
    this->current = Token(DECIMAL, res);

    return true;
  }

  return false;
}

bool Lexer::test_token_table() {
  vector<string> ks;
  for (const auto [k, v] : VALUE_TOKEN_TABLE) {
    ks.push_back(k);
  }
  for (const auto k : ks) {
    if (this->test_in_token_table(k)) return true;
  }
  return false;
}

bool Lexer::test_whitespace() {
  string res = "";
  while (!this->source.finished()) {
    if (!is_whitespace(this->source.lookahead)) break;
    res.push_back(this->source.lookahead);
    this->source.advance();
  }
  if (res != "") {
    this->current = Token(WHITESPACE, res);

    return true;
  } else {
    return false;
  }
}

bool Lexer::next_token() {
  // Always go dynamic token check first
  // Fuck it, actually should go static otkne check first, but annoying :(
   bool res =
    this->test_token_table() ||
    this->test_whitespace() ||
    this->test_ident() ||
    this->test_decimal() ||
    this->test_string();

  if (res) {
    this->tokens.push_back(this->current.copy());
  }

  return res;
}

void Lexer::debug(bool show_space) {
  cout << "[" << endl;
  for (const auto t : this->tokens) {
    if (!show_space && t.type == WHITESPACE) continue;
    cout << "  (" << DEBUG_INFO.at(t.type) << " " << t.value << ")" << endl;
  }
  cout << "]" << endl;
}
