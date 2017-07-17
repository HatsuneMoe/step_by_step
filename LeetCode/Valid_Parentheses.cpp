#include <iostream>
#include <stack>

using std::string;
using std::stack;

class Solution {
public:
    bool isValid(string s) {
        stack<char> _stack;
        for (auto &i: s){
            if (i == '(' || i == '{' || i == '[') _stack.push(i);
            if (i == ')')if (_stack.empty() || _stack.top() != '(') return false; else _stack.pop();
            else if (i == ']')if (_stack.empty() || _stack.top() != '[') return false; else _stack.pop();
            else if (i == '}')if (_stack.empty() || _stack.top() != '{') return false; else _stack.pop();
        }
        return _stack.empty();
    }
};

int main()
{
    Solution A;
    std::cout << A.isValid("]") << std::endl;
    return 0;
}