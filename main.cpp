#include <bits/stdc++.h>

#include "ast_node.hpp"
#include "token.hpp"

using namespace std;

vector<Token> tokenizer(string input) {
  int current = 0;
  vector<Token> tokens;

  while (current < input.size()) {
    string curr_char = string(1, input[current]);

    if (curr_char == "(") {
      tokens.push_back(Token("paren", "("));
      ++current;
      continue;
    }

    if (curr_char == ")") {
      tokens.push_back(Token("paren", ")"));
      ++current;
      continue;
    }

    if (regex_match(curr_char, regex("\\s"))) {
      ++current;
      continue;
    }

    if (regex_match(curr_char, regex("[0-9]"))) {
      string value;
      while (regex_match(curr_char, regex("[0-9]"))) {
        value += curr_char;
        curr_char = string(1, input[++current]);
      }

      tokens.push_back(Token("number", value));
      continue;
    }

    if (regex_match(curr_char, regex("[a-z]"))) {
      string value;
      while (regex_match(curr_char, regex("[a-z]"))) {
        value += curr_char;
        curr_char = string(1, input[++current]);
      }

      tokens.push_back(Token("name", value));
      continue;
    }

    ++current;
  }

  return tokens;
}

AstNode* traversal(vector<Token>& tokens, int& current) {
  Token token = tokens[current];

  if (token.type == "number") {
    ++current;
    cout << "NumberLiteral" << endl;
    return new AstNode("NumberLiteral", token.value);
  }

  if (token.type == "paren" && token.value == "(") {
    token = tokens[++current];

    cout << "CallExpression start" << endl;
    AstNode* node =
        new AstNode("CallExpression", token.value, vector<AstNode*>({}));
    token = tokens[++current];

    while ((token.type != "paren") ||
           (token.type == "paren" && token.value != ")")) {
      node->params.push_back(traversal(tokens, current));
      token = tokens[current];
    }

    cout << "CallExpression end" << endl;
    ++current;
    return node;
  }
}

AstNode* parser(vector<Token> tokens) {
  int current = 0;

  cout << '\n';
  cout << "========== Traversal ============" << '\n';

  AstNode* ast = new AstNode("Program");
  while (current < tokens.size()) {
    ast->body.push_back(traversal(tokens, current));
  }
  cout << "========== End ============" << '\n';
  cout << '\n';

  return ast;
};

int main() {
  vector<Token> tokens = tokenizer("(add 1 )");

  vector<Token>::iterator it;

  for (it = tokens.begin(); it != tokens.end(); it++) {
    cout << it->type << ' ';
    cout << it->value << '\n';
  }

  AstNode* ast = parser(tokens);

  return 0;
}