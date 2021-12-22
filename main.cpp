#include <bits/stdc++.h>

#include "ast_node.hpp"
#include "token.hpp"
#include "transformer.hpp"

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
  throw runtime_error("Unknown Type: " + token.type);
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

string codeGenerator(AstNode* node) {
  string gencode;

  if (node->type == "Program") {
    for (auto item : node->body) {
      gencode += codeGenerator(item) + "\n";
    }
    return gencode;
  } else if (node->type == "ExpressionStatement") {
    return codeGenerator(node->expression) + ";";
  } else if (node->type == "CallExpression") {
    gencode += codeGenerator(node->callee) + "(";
    auto arguments = (*node->arguments);
    for (int i = 0; i < arguments.size(); ++i) {
      if (i == arguments.size() - 1) {
        gencode += codeGenerator(arguments[i]);
      } else {
        gencode += codeGenerator(arguments[i]) + ",";
      }
    }
    gencode += ")";
    return gencode;
  } else if (node->type == "Identifier") {
    return node->name;
  } else if (node->type == "NumberLiteral") {
    return node->name;
  } else if (node->type == "StringLiteral") {
    return "\"" + node->name + "\"";
  } else {
    throw runtime_error("codeGenerator: unknow astnode type" + node->type);
  }
}

void printTokens(vector<Token> tokens) {
  cout << "========= Tokens: ==========" << endl;
  for (auto to : tokens) {
    cout << to.type << " " << to.value << endl;
  }
  cout << "========== End Of Tokens ==========" << endl;
}

int main() {
  vector<Token> tokens = tokenizer("(add 4 (subtract 23 8))");

  printTokens(tokens);

  AstNode* ast = parser(tokens);

  Transformer trans(ast);
  AstNode* new_ast = trans.traversal();

  string generated_code = codeGenerator(new_ast);

  cout << generated_code << '\n';

  return 0;
}