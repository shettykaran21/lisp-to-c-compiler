#include <bits/stdc++.h>

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

    ++current;
  }

  return tokens;
}

int main() {
  vector<Token> tokens = tokenizer("(1 )");

  vector<Token>::iterator it;

  for (it = tokens.begin(); it != tokens.end(); it++) {
    cout << it->type << ' ';
    cout << it->value << '\n';
  }

  return 0;
}