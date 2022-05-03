// Copyright 2022 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int prior(char c) {
  if (c == '(')
    return 0;
  else if ( c == ')')
    return 1;
  else if (c == '+' || c == '-')
    return 2;
  else if ( c == '*' || c == '/')
    return 3;
  else if (c == ' ')
    return 4;
  else
    return 5;
}
std::string infx2pstfx(std::string inf) {
  std::string outp;
  TStack <char, 100> ts;
  const char pr = ' ';
  for (int i = 0; i < inf.length(); i++) {
    if (prior(inf[i]) == 5) {
      outp += inf[i];
      outp += pr;
    } else if (ts.isEmpty() || prior(inf[i]) == 0
                     || (prior(inf[i]) > prior(ts.get()))) {
      ts.push(inf[i]);
    } else if (prior(inf[i]) == 1) {
      while (prior(ts.get()) != 0) {
        outp += ts.get();
        outp += pr;
        ts.pop();
      }
      ts.pop();
    } else if (prior(inf[i]) <= prior(ts.get())) {
      while (prior(ts.get()) > 1 && !ts.isEmpty()) {
        outp += ts.get();
        outp += pr;
        ts.pop();
      }
      ts.push(inf[i]);
    }
  }
while (!ts.isEmpty()) {
  outp += ts.get();
  outp += pr;
  ts.pop();
  }
    outp.pop_back();
  return outp;
}

int eval(std::string pref) {
  std::string outp;
  TStack<int, 100> ts2;
  int res;
  for (int i = 0; i < pref.length(); i++) {
    std::string ch;
    while (5 == prior(pref[i])) {
      ch += pref[i];
      i += 1;
    }
    if (ch != "") {
      ts2.push(std::stoi(ch));
    }
    if (2 == prior(pref[i]) || 3 == prior(pref[i])) {
      int a = ts2.get();
      ts2.pop();
      int b = ts2.get();
      ts2.pop();
      if ('-' == pref[i]) {
        res = b - a;
        ts2.push(res);
      } else if ('+' == pref[i]) {
        res = a + b;
        ts2.push(res);
      } else if ('*' == pref[i]) {
        res = a * b;
        ts2.push(res);
      } else if ('/' == pref[i]) {
        res = b / a;
        ts2.push(res);
      }
    }
  }
  res = ts2.get();
  return res;
}
