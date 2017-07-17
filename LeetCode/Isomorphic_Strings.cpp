#include <iostream>
#include <unordered_map>
#include <bitset>

using std::bitset;
using std::string;
using std::unordered_map;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        char hash_table[256] = {0};
        bitset<256> is_dup = {0};
        for (int i=0; i<s.size(); ++i){
            if (hash_table[s[i]] == 0 && is_dup[t[i]] != 1){
                hash_table[s[i]] = t[i];
                is_dup[t[i]] = 1;
            } else
                if (hash_table[s[i]] != t[i])
                    return false;
        }
        return true;
    }
};

int main()
{
    Solution A;
    std::cout << A.isIsomorphic("abc", "efe") << std::endl;
    return 0;
}