#include <string>
#include <map>
using namespace std;

enum TokenType {
  KW_IMPORT, // 'import'
  KW_WHERE, // 'where'
  NUM, // /[1-9]*/
  IDENT, // /[a-z1-9_$']*/
  ARROW_LEFT, // <
  ARROW_RIGHT, // >
  STAR, // *
  HASH, // #
  DOT, // .
  UNDERSCORE, // _
  AND, // &
  PERCENTAGE, // %
  AT, // @
  PLUS, // +
  MINUS, // -
  DIV, // /

  INVALID, // Invalid token
  EMPTY, // Uninitialized empty token
};

template <typename K, typename V>
static inline map<V, K> reverse(const map<K, V> original) {
  map<V, K> res;
  for (const auto [key, value] : original) {
    res[value] = key;
  }

  return res;
}
static const map<string, TokenType> VALUE_TOKEN_TABLE {
  { "import", KW_IMPORT },
  { "where", KW_WHERE },
  { "<", ARROW_LEFT },
  { ">", ARROW_RIGHT },
  { "*", STAR },
  { "#", HASH },
  { ".", DOT },
  { "_", UNDERSCORE },
  { "&", AND },
  { "%", PERCENTAGE },
  { "@", AT },
  { "+", PLUS },
  { "-", MINUS },
  { "/", DIV },
};
static const map<TokenType, string> TOKEN_VALUE_TABLE = reverse(VALUE_TOKEN_TABLE);

class Token {
public:
  TokenType type;
  string value;

  Token(TokenType type, string value);
  Token(string value);
  ~Token();
};

static const string WHITESPACES = " \t\n\0\r";
static const string LINEBREAKS = "\n\r\0";

bool is_whitespace(char ch);
bool is_linebreak(char ch);
bool valid_ident(string ident);

class Cursor {
public:
  int index;
  int row;
  int col;
};

class RawSource {
private:
  bool is_started;
public:
  string source;
  Cursor cursor;
  // Necessity: `advance` may do nothing
  char lookahead;

  RawSource(string source);
  ~RawSource();

  void advance();
  void advance_by(int n);
  bool expect(string str);

  RawSource peekable();
  bool finished();
};
