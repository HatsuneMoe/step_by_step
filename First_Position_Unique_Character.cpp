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
        unordered_map<char, int> count_table;

        for(auto item :s)
            count_table[item]++;

        for(int index=0; index<s.size(); index++)
            if(count_table[s[index]] == 1)
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