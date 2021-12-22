#ifndef TRANSFORMER_HPP
#define TRANSFORMER_HPP

#include <bits/stdc++.h>

#include "ast_node.hpp"

using namespace std;

class Transformer {
 private:
  map<string, function<void(AstNode*, AstNode*, bool)>> visitors;
  AstNode* AST;

 public:
  Transformer(AstNode* AST);
  void traverseNode(AstNode* node, AstNode* parent);
  void traverseArray(vector<AstNode*>* nodes, AstNode* parent);
  AstNode* traversal();
};

#endif