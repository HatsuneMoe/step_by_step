#include <iostream>

using std::string;

class Solution {
public:
    string reverseString(string s) {
        int i = 0, j = s.size()-1;
        while (i < j){
            if (s[i] != s[j]){
                s[i] = s[i]^s[j];
                s[j] = s[i]^s[j];
                s[i] = s[i]^s[j];
            }
            i++, j--;
        }
        return s;
    }
};

int main()
{
    Solution A;
    std::cout << A.reverseString("Hello, World!") << std::endl;
    return 0;
}