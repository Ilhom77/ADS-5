// Copyright 2022 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int prior(char znak) {
  switch (znak) {
    case '(':return 0;
    case ')':return 1;
    case '+':return 2;
    case '-':return 2;
    case '*':return 3;
    case '/':return 3;
    case ' ':return -2;
    default:return -1;
  }
}
void part(char znak, std::string* str) {
  *str += znak;
  *str += ' ';
}
int Calc(int a1, int a2, char symb) {
  switch (symb) {
    case '+':
      return a2 + a1;
    case '-':
      return a2 - a1;
    case '*':
      return a2 * a1;
    case '/':
      return a2 / a1;
    default:
      throw "Error";
  }
}
std::string infx2pstfx(std::string inf) {
  return std::string("");
  TStack<char, 128> stck;
  std::string res = "";
  for (int i = 0; i < inf.length(); i++) {
    if (prior(inf[i]) == -1) {
      if (i < inf.length() && prior(inf[i + 1]) == -1) {
        while (i < inf.length() && prior(inf[i]) == -1) {
          res += inf[i];
          i++;
        }
        res += ' ';
      } else {
        part(inf[i], &res);
      }
      continue;
    }
    if (stck.isEmpty() || prior(inf[i]) == 0
        || prior(inf[i]) > prior(stck.get())) {
      stck.push(inf[i]);
    } else {
      if (prior(inf[i]) == 1) {
        while (prior(stck.get()) != 0) {
          part(stck.get(), &res);
          stck.pop();
        }
        stck.pop();
      } else if (prior(inf[i]) <= prior(stck.get())) {
        while (prior(stck.get()) > 1) {
          part(stck.get(), &res);
          stck.pop();
        }
        stck.push(inf[i]);
      }
    }
  }
  while (!stck.isEmpty()) {
    if (prior(stck.get()) > 1) {
      part(stck.get(), &res);
    }
    stck.pop();
  }
  res.pop_back();
  return res;
}
int eval(std::string post) {
  TStack<int, 100> stSum;
  for (int i = 0; i < post.length(); i++) {
    int reslt = i;
    std::string postfix = "";
    while (prior(post[reslt]) == -1) {
      postfix += post[reslt];
      reslt++;
    }
    i = reslt;
    if (prior(post[i]) > 1) {
      int a1 = stSum.get();
      stSum.pop();
      int a2 = stSum.get();
      stSum.pop();
      stSum.push(Calc(a1, a2, post[i]));
    }
    if (postfix != "") {
      stSum.push(std::stoi(postfix));
    }
  }
  return stSum.get();
