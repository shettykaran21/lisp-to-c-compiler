#include "token.hpp"

using namespace std;

Token::Token(string type, string value) {
  this->type = type;
  this->value = value;
}