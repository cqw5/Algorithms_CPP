/*! Author: qwchen
 *! Date: 2016-9-19
 * 用栈实现的括号匹配问题
 * 问题描述：对一个字符串中的括号进行匹配
 * 思路：如果从左到右地扫描字符串，那么每一个右括号都与最近扫描的那个未匹配的左括号相匹配。
 *       可是设计一个栈，每次遇到左括号就将左括号入栈，每次遇到右括号就将它与栈顶的左括号相匹配，并将匹配的左括号从栈顶删除
 * 时间复杂度：O(n)
 */

#include <string>
#include <iostream>
#include <stack>

using namespace std;

void matchedPairs(string expr) {
    stack<char> s;
    int lenExpr = (int)expr.length();
    bool flag = true;
    for (int i = 0; i < lenExpr; i++) {
        if (expr.at(i) == '(') {
            s.push(expr.at(i));
        }
        else if (expr.at(i) == ')') {
            try {
                s.pop();
            }
            catch (range_error) {
                flag = false;
                cout << "No match for right parenthsis" << endl;
            }
        }
    }
    while (!s.empty()) {
        flag = false;
        cout << "No match for left parenthesis" << endl;
        s.pop();
    }
    if (flag)
        cout << "syntax is right, all parentheis have matched" << endl;
    else
        cout << "syntax error" << endl;
}

void testMatcheddPairs() {
    matchedPairs("(a*(b+c)+d)");
    matchedPairs("a*(b+c)+d)");
}

int main(){
    testMatcheddPairs();
    return 0;
}