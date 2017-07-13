#include <vector>
#include <iostream>

using std::vector;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int res = 0, count = 0;
        for (auto &i : nums){
            if (count == 0) res = i;
            if (i == res) count++;
            else count--;
        }
        return res;
    }
};

int main()
{
    Solution A;
    vector<int> _list = {1,2,3,4,1};
    std::cout << A.majorityElement(_list) << std::endl;
    return 0;
}