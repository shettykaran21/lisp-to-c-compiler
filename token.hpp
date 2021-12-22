#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>

using namespace std;

class Token {
 public:
  string type;
  string value;
  Token(string type, string value);
};

#endif
