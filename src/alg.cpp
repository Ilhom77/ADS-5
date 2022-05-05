// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
std::string infx2pstfx(std::string inpt) {
    TStack<char, 100> stack1;
    std::string res;
    int len = inpt.length();
    for (int i = 0; i < len; i++) {
        if ('0' <= inpt[i] && inpt[i] <= '9') {
            res += inpt[i];
            //res += " ";
        } else if (inpt[i] == '(') {
            stack1.push(inpt[i]);
        } else if ((inpt[i] == '+' || inpt[i] == '-') &&
            (stack1.get() != '*') &&
            (stack1.get() != '/') && (stack1.get() != '+') &&
            (stack1.get() != '-')) {
            stack1.push(inpt[i]);
        } else if ((inpt[i] == '*') &&
            ((stack1.get() != '*') && (stack1.get() != '/') ||
                (stack1.get() == '+') || (stack1.get() == '-'))) {
            stack1.push(inpt[i]);
        } else if ((inpt[i] == '/') && ((stack1.get() != '*') &&
            (stack1.get() != '/') ||
            (stack1.get() == '+') || (stack1.get() == '-'))) {
            stack1.push(inpt[i]);
        } else if (inpt[i] == ')') {
            while (stack1.get() != '(') {
                res += stack1.get();
                //res += " ";
                stack1.pop();
            }
            stack1.pop();
        } else {
            if (inpt[i] == '+' || inpt[i] == '-') {
                while ((stack1.get() != '(') && (!stack1.isEmpty())) {
                    res += stack1.get();
                    //res += " ";
                    stack1.pop();
                }
                stack1.push(inpt[i]);
            }
            if (inpt[i] == '*' || inpt[i] == '/') {
                while ((stack1.get() == '*' || stack1.get() == '/') &&
                    (!stack1.isEmpty())) {
                    res += stack1.get();
                    //res += " ";
                    stack1.pop();
                }
                stack1.push(inpt[i]);
            }
        }
    }
    while (!stack1.isEmpty()) {
        res += stack1.get();
        stack1.pop();
    }
    std::string out;
    len = res.length();
    //std::cout << len << "##" << res << "\n";
    for (int i = 0; i <= len - 1; i++) {
        //printf("%i#%c#\n", i, res[i]);
        out += res[i];
        if (!(i == len - 1)) out += " ";
    }
    return out;
}
int eval(std::string inpt) {
    TStack<int, 100> stack2;
    int len = inpt.length();
    for (int i = 0; i < len; i++) {
        if ('0' <= inpt[i] && inpt[i] <= '9') {
            int x = inpt[i] - '0';
            stack2.push(x);
        }
        if (inpt[i] == '+') {
            int a = stack2.get();
            stack2.pop();
            int b = stack2.get();
            stack2.pop();
            int c = b + a;
            stack2.push(c);
        }
        if (inpt[i] == '-') {
            int a = stack2.get();
            stack2.pop();
            int b = stack2.get();
            stack2.pop();
            int c = b - a;
            stack2.push(c);
        }
        if (inpt[i] == '*') {
            int a = stack2.get();
            stack2.pop();
            int b = stack2.get();
            stack2.pop();
            int c = b * a;
            stack2.push(c);
        }
        if (inpt[i] == '/') {
            int a = stack2.get();
            stack2.pop();
            int b = stack2.get();
            stack2.pop();
            int c = b / a;
            stack2.push(c);
        }
    }
    int res = stack2.get();
    stack2.pop();
    return res;
}
