// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include <stack>

int check(char i) {
    if (i == '/' || i == '*') {
        return 3;
    } else if (i == '+' || i == '-') {
        return 2;
    } else {
        return 1;
    }
}

std::string infx2pstfx(std::string s) {
    std::string st = "";
    std::stack<char> Stack;
    for (int i = 0; i < s.length(); i++) {
        char ch = s[i];
        if ((ch >= '0' && ch <= '9')) {
            st += ch;
            for (int j = i + 1; j < s.length(); j++) {
                if ((s[j] >= '0' && s[j] <= '9')) {
                    i += 1;
                    st += s[j];
                } else {
                    break;
                }
            }
            st += " ";
        } else if (ch == '(') {
            Stack.push('(');
        } else if (ch == ')') {
            while (Stack.top() != '(') {
                st += Stack.top();
                st += " ";
                Stack.pop();
            }
            Stack.pop();
        } else {
            while (!Stack.empty() && check(s[i]) <= check(Stack.top())) {
                st += Stack.top();
                st += " ";
                Stack.pop();
            }
            Stack.push(ch);
        }
    }
    while (!Stack.empty()) {
        st += Stack.top();
        st += " ";
        Stack.pop();
    }
    if (st[st.length() - 1] == ' ') {
        st.pop_back();
    }
    return st;
}

int eval(std::string s) {
    std::string p;
    std::stack<int> Stack;
    for (int i = 0; i < s.length(); ++i) {
        p = "";
        if ((s[i] >= '0' && s[i] <= '9')) {
            p += s[i];
            for (int j = i + 1; j < s.length(); j++) {
                if ((s[j] >= '0' && s[j] <= '9')) {
                    i += 1;
                    p += s[j];
                } else {
                    break;
                }
            }
            Stack.push(std::stoi(p));
        } else if (s[i] != ' ') {
            int first, second;
            first = Stack.top();
            Stack.pop();
            second = Stack.top();
            Stack.pop();
            if (s[i] == '+') {
                Stack.push(second + first);
            }
            if (s[i] == '-') {
                Stack.push(second - first);
            }
            if (s[i] == '*') {
                Stack.push(second * first);
            }
            if (s[i] == '/') {
                Stack.push(second / first);
            }
        }
    }
    return Stack.top();
}
