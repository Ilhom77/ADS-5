// Copyright 2022 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int pr(char op) {
    switch (op) {
      case '(': return 0;
      case ')': return 1;
      case '+': return 2;
      case '-': return 2;
      case '*': return 3;
      case '/': return 3;
      case ' ': return 4;
      default: return 5; //цифры
    }
  }

int culcul(char op, int a, int b) {
  switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    default: return 0;
  }
}
std::string infx2pstfx(std::string inf) {
  std::string res;
  TStack <char, 100> sta;
  for (int i = 0; i < inf.length(); i++) {
    if (pr(inf[i]) == 5) {
      res.push_back(inf[i]); //цифры сразу в строку с пробелом
      res.push_back(' ');
    } else {
        if (pr(inf[i]) == 4) {
          continue; //пропускаем пробел
        } else if (pr(inf[i]) == 0) {
          sta.push(inf[i]);
        } else if (pr(inf[i]) > pr(sta.get())) {
          sta.push(inf[i]);
        } else if (sta.isEmpty()) {
          sta.push(inf[i]);
        } else if (pr(inf[i]) == 1) {
          while (pr(sta.get()) != 0) { //до открытой скобки
            res.push_back(sta.get());
            res.push_back(' ');
            sta.pop(); //удаление скобки
          }
          sta.pop();
        } else {
            while (!sta.isEmpty() && (pr(inf[i]) <= pr(sta.get()))) {
              res.push_back(sta.get());
              res.push_back(' ');
              sta.pop();
            }
            sta.push(inf[i]);
        }
     }
  }
  while (!sta.isEmpty()) { //извлечение остатка
    res.push_back(sta.get());
    res.push_back(' ');
    sta.pop();
  }
  res.pop_back();
  return res;
}
int eval(std::string pref) {
  TStack <int, 100> stack2;
  int res = 0, x, y;
  for (int i = 0; i < pref.length(); i++) {
    if (pr(pref[i]) == 5) {
      stack2.push(pref[i]-'0');
    } else if (pr(pref[i]) < 4) {
      y = stack2.get();
      stack2.pop();
      x = stack2.get();
      stack2.pop();
      stack2.push(culcul(pref[i], x, y)); //результат предыдущего действия
    }
  }
  res = stack2.get();
  return res;
}
