#ifndef AST_NODE_HPP
#define AST_NODE_HPP

#include <bits/stdc++.h>

#include <iostream>

using namespace std;

class AstNode {
 public:
  string type;
  string name;
  string value;

  AstNode* callee = nullptr;
  AstNode* expression = nullptr;

  vector<AstNode*> body;
  vector<AstNode*> params;
  vector<AstNode*>* arguments;
  vector<AstNode*>* context;

  AstNode(string type);
  AstNode(string type, vector<AstNode*> body);
  AstNode(string type, string name);
  AstNode(string type, string name, vector<AstNode*> params);
  AstNode(string type, AstNode* callee, vector<AstNode*>* arguments);
};

#endif