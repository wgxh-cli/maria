#include <map>
#include <stack>
#include <vector>
#include "lexer.h"
using namespace std;

namespace parser {
#define AST_NODE_TYPES \
X(ROOT, "ROOT") \
X(EXPR, "HELLo") \
X(DECLARATION, "DECL") \
X(IDENT, "IDENT") \
X(UNINITIALIZED, "INVALID") \

#define X(a, b) a,
enum ASTNodeType {
  AST_NODE_TYPES
};
#undef X

#define X(a, b) {a, b},
static const map<ASTNodeType, string> AST_DEBUG_TABLE {
  AST_NODE_TYPES
};
#undef X

struct Span {
  Cursor start;
  Cursor end;

  Span(Cursor start, Cursor end);
  static const Span unintialized();
};

class ASTNode {
public:
  ASTNodeType type;
  Span span;
  vector<ASTNode> next;
  string value;

  ASTNode(ASTNodeType type, Span span, string value = "");
  ~ASTNode();
};

class PendingNode {
public:
  Cursor start;
  unsigned int depth;

  PendingNode(Cursor start, unsigned int depth);
};

class Parser {
public:
  Lexer lexer;
  ASTNode root;
  vector<ASTNode> current_buf;
  stack<PendingNode> pending_stack;
  int current_depth;
  int prev_depth;
  bool finished;

  Parser(Lexer lexer);
  ~Parser();

  void mark_start();
  void mark_end(ASTNodeType type);

  void debug();
};
}
