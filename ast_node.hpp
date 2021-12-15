#include <bits/stdc++.h>

#include <iostream>

using namespace std;

class AstNode {
 public:
  string type;
  string name;
  string value;

  vector<AstNode*> body;
  vector<AstNode*> params;

  AstNode(string type);
  AstNode(string type, vector<AstNode*> body);
  AstNode(string type, string name);
  AstNode(string type, string name, vector<AstNode*> params);
};