#include <string>
#include <map>
using namespace std;

#define DYN_TOKENS \
X(IDENT, "IDENT") \
X(STRING, "STRING") \
X(DECIMAL, "DECIMAL") \
X(WHITESPACE, "WHITESPACE") \

#define STATIC_TOKENS \
X(KW_IMPORT, "import") \
X(KW_WHERE, "where") \
X(KW_IF, "if") \
X(KW_THEN, "then") \
X(KW_ELSE, "else") \
X(KW_CASE, "case") \
X(KW_OF, "of") \
X(KW_EXTERN, "extern") \
X(KW_LET, "let") \
X(KW_IN, "in") \
X(ARROW_LEFT, "<") \
X(ARROW_RIGHT, ">") \
X(STAR, "*") \
X(HASH, "#") \
X(DOT, ".") \
X(UNDERSCORE, "_") \
X(AND, "&") \
X(PERCENTAGE, "%") \
X(AT, "@") \
X(PLUS, "+") \
X(MINUS, "-") \
X(DIV, "/") \
X(L_BRACKET, "[") \
X(R_BRACKET, "]") \
X(L_BRACE, "{") \
X(R_BRACE, "}") \
X(L_PAREN, "(") \
X(R_PAREN, ")") \
X(SEMICOLON, ";") \
X(COLON, ":") \
X(EQUAL, "=") \
X(POWER, "^") \
X(COMMA, ",") \

#define OTHER_TOKENS \
X(EMPTY, "EMPTY") \

#define TOKEN_TYPES \
DYN_TOKENS \
STATIC_TOKENS \
OTHER_TOKENS \

#define X(a, b) a,
enum TokenType {
  TOKEN_TYPES
};
#undef X
#define X(a, b) { a, b },
static const map<TokenType, string> DEBUG_INFO {
  TOKEN_TYPES
};
#undef X

template <typename K, typename V>
static inline map<V, K> reverse(const map<K, V> original) {
  map<V, K> res;
  for (const auto [key, value] : original) {
    res[value] = key;
  }

  return res;
}
#define X(a, b) { b, a },
static const map<string, TokenType> VALUE_TOKEN_TABLE {
  STATIC_TOKENS
};
#undef X
static const map<TokenType, string> TOKEN_VALUE_TABLE = reverse(VALUE_TOKEN_TABLE);

class Token {
public:
  TokenType type;
  string value;

  Token(TokenType type, string value);
  Token(string value);
  Token copy();
  ~Token();
};

static const string WHITESPACES = " \t\n\0\r";
static const string LINEBREAKS = "\n\r\0";

bool is_whitespace(char ch);
bool is_linebreak(char ch);

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
