#include <iostream>
#include <string>
#include <unordered_map>

using std::cout;
using std::endl;
using std::unordered_map;
using std::string;

class Solution {
public:
    int firstUniqChar(string s) {
        int count[256] = {0};

        for(auto &item :s)
            count[(int)item]++;

        for(int index=0; index<s.size(); index++)
            if(count[(int)s[index]] == 1)
                return index;

        return -1;
    }
};



int main()
{
    Solution A;
    std::cout << A.firstUniqChar("llttccoodde") << std::endl;
    return 0;
}
