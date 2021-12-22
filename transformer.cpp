#include "transformer.hpp"

#include "ast_node.hpp"

void NumberLiteral_Visitor(AstNode* node, AstNode* parent, bool exit) {
  if (!exit) {
    (*parent->context).push_back(new AstNode("NumberLiteral", node->name));
  }
}

void StringLiteral_Visitor(AstNode* node, AstNode* parent, bool exit) {
  if (!exit) {
    (*parent->context).push_back(new AstNode("StringLiteral", node->name));
  }
}

void CallExpression_Visitor(AstNode* node, AstNode* parent, bool exit) {
  if (!exit) {
    AstNode* callee = new AstNode("Identifier", node->name);
    AstNode* callExpr =
        new AstNode("CallExpression", callee, new vector<AstNode*>());
    node->context = callExpr->arguments;

    if (parent != nullptr) {
      if (parent->type != "CallExpression") {
        AstNode* expr = new AstNode("ExpressionStatement");
        expr->expression = callExpr;
        callExpr = expr;
      }
      (*parent->context).push_back(callExpr);
    }
  }
}

Transformer::Transformer(AstNode* AST) {
  this->AST = AST;
  visitors["NumberLiteral"] = &NumberLiteral_Visitor;
  visitors["StringLiteral"] = &StringLiteral_Visitor;
  visitors["CallExpression"] = &CallExpression_Visitor;
  visitors["Program"] = &CallExpression_Visitor;
}

void Transformer::traverseNode(AstNode* node, AstNode* parent) {
  cout << node->type << endl;
  auto visitor = visitors[node->type];
  visitor(node, parent, false);

  if (node->type == "Program") {
    traverseArray(&(node->body), node);
  } else if (node->type == "CallExpression") {
    traverseArray(&(node->params), node);
  } else if (node->type == "NumberLiteral" || node->type == "StringLiteral") {
  } else {
    throw runtime_error("unknown node type " + node->type);
  }
  visitor(node, parent, true);
}

void Transformer::traverseArray(vector<AstNode*>* nodes, AstNode* parent) {
  for (int i = 0; i < (*nodes).size(); ++i) {
    traverseNode((*nodes)[i], parent);
  }
}

AstNode* Transformer::traversal() {
  cout << "========== Traversal ============" << endl;
  AstNode* new_ast = new AstNode("Program");
  traverseNode(AST, nullptr);
  new_ast->body = (*AST->context);
  cout << "========== End of Traversal ============" << endl;
  return new_ast;
}