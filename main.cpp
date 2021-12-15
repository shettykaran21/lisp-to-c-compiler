#include "token.hpp"

int main() {
  Token *t = new Token("karan", "atharva");

  cout << t->type;

  return 0;
}