#include <iostream>
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int> res;
        unordered_map<int, int> hash_map;
        for (auto &i: nums1)
            hash_map[i]++;
        for (auto &j: nums2)
            if (--hash_map[j] >= 0)
                res.push_back(j);
        return res;
    }
};


int main()
{
    Solution A;
    vector<int> a = {1, 2, 2, 1}, b = {2, 2};
    for (auto &i: A.intersect(a, b))
        std::cout << i << std::endl;
    return 0;
}