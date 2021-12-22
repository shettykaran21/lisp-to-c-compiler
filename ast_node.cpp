#include "ast_node.hpp"

AstNode::AstNode(string type) { this->type = type; }

AstNode::AstNode(string type, vector<AstNode*> body) {
  this->type = type;
  this->body = body;
}

AstNode::AstNode(string type, string name) {
  this->type = type;
  this->name = name;
}

AstNode::AstNode(string type, string name, vector<AstNode*> params) {
  this->type = type;
  this->name = name;
  this->params = params;
}

AstNode::AstNode(string type, AstNode* callee, vector<AstNode*>* arguments) {
  this->type = type;
  this->callee = callee;
  this->arguments = arguments;
}