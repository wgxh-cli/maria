#include <iostream>
#include "includes/parser.h"

using namespace std;
using namespace parser;

const Span Span::unintialized() {
  Cursor start = Cursor();
  Cursor end = Cursor();
  Span span(start, end);

  return span;
}

Span::Span(Cursor start, Cursor end) : start(start), end(end) {}

PendingNode::PendingNode(Cursor start, unsigned int depth) : start(start), depth(depth) {}

ASTNode::ASTNode(ASTNodeType type, Span span, string value) : type(type), span(span), value(value) {}
ASTNode::~ASTNode() {}

Parser::Parser(Lexer lexer) :
  lexer(lexer),
  root(UNINITIALIZED, Span::unintialized()),
  current_depth(0),
  finished(false),
  prev_depth(-1)
{}
Parser::~Parser() {}

void Parser::mark_start() {
  PendingNode pending(lexer.source.cursor.copy(), current_depth);
  this->current_depth += 1;
  this->pending_stack.push(pending);
}

void Parser::mark_end(ASTNodeType type, string value) {
  if (finished) return;

  if (pending_stack.empty()) return;
  PendingNode pending = pending_stack.top();
  cout << pending.depth << " " << current_depth << endl;

  Span span = Span(pending.start, lexer.source.cursor.copy());
  ASTNode node(type, span, value);

  if (prev_depth == pending.depth) {
    current_buf.push_back(node);
  } else {
    node.next = current_buf;
    current_buf.clear();

    current_buf.push_back(node);
  }

  prev_depth = pending.depth;
  if (pending.depth == 0) {
    root = node;
    finished = true;
  }

  current_depth -= 1;
  pending_stack.pop();
}

void Parser::cancel() {
  if (pending_stack.empty()) return;
  pending_stack.pop();
}

Parser Parser::copy() {
  Parser parser(lexer.copy());
  parser.pending_stack = pending_stack;
  parser.root = root;
  parser.prev_depth = parser.prev_depth;
  parser.current_buf = parser.current_buf;
  parser.finished = finished;
  parser.current_depth = current_depth;

  return parser;
}

bool Parser::test_ident() {
  FakeLexer fake = FakeLexer(&lexer);
  mark_start();
  if (fake.next_token()) {
    if (fake.current.type == TokenType::IDENT) {
      mark_end(ASTNodeType::IDENT, fake.current.value);
      fake.merge(&lexer);

      return true;
    }
  }

  cancel();
  return false;
}

bool Parser::test_decl() {
  FakeLexer fake = FakeLexer(&lexer);
  mark_start();
  if (test_ident()) {
    if (fake.next_token()) {

    }
  }

  cancel();
  return false;
}

void debug_depth(ASTNode node, unsigned int depth) {
  string indent = "";
  for (int i = 0; i < depth; i++) {
    indent += "  ";
  }
  cout << indent << "(" << AST_DEBUG_TABLE.at(node.type);
  if (node.value != "") {
    cout << " " << node.value;
  }
  for (ASTNode node : node.next) {
    cout << endl;
    debug_depth(node, depth + 1);
  }
  cout << ")";
}

void Parser::debug() {
  if (!finished) {
    cout << "Not finished yet" << endl;
    return;
  }
  debug_depth(root, 0);
}
