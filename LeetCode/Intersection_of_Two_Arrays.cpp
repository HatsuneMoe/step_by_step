#include <iostream>
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> res;
        unordered_map<int, int> hash_map;
        for (auto &i: nums1)
            hash_map[i] = 1;
        for (auto &i: nums2)
            if (hash_map[i] == 1) hash_map[i] = 2;
        for (auto &i: hash_map)
            if (i.second == 2) res.push_back(i.first);
        return res;
    }
};

int main()
{
    Solution A;
    vector<int> a = {1, 2, 2, 1}, b = {2, 2};
    for (auto &i: A.intersection(a, b))
        std::cout << i << std::endl;
    return 0;
}