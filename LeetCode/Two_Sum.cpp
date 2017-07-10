#include <iostream>
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int index = 0;
        unordered_map<int, int> m_hm;
        for (auto i : nums) {
            if (m_hm.count(i) != 0) {
                vector<int> ret_res = { m_hm[i], index };
                if (m_hm[i] > index) {
                    ret_res[0] ^= ret_res[1];
                    ret_res[1] ^= ret_res[0];
                    ret_res[0] ^= ret_res[1];
                }
                return ret_res;
            }
            if (m_hm.count(target-i) == 0)
                m_hm[target - i] = index;
            index++;
        }
    }
};

int main()
{
    Solution A;
    vector<int> a = {3, 3, 1};
    for (auto i : A.twoSum(a, 6))
        std::cout << i << " ";
    return 0;
}