#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> result;
        int length = nums.size() / 3;
        int res_1, res_2;
        int c_res_1 = 0, c_res_2 = 0;
        int ck_1 = 0, ck_2=0;
        for (int i=0; i<nums.size(); ++i){
            if (c_res_1 == 0 && nums[i] != res_2)
                res_1 = nums[i];
            else if (c_res_2 == 0 && nums[i] != res_1)
                res_2 = nums[i];

            if (res_1 == nums[i])
                c_res_1++;
            else if (res_2 == nums[i])
                c_res_2++;
            else {
                if (c_res_1 > 0 && --c_res_1 == 0)
                    res_1 = nums[i];
                if (c_res_2 > 0 && --c_res_2 == 0)
                    res_2 = nums[i];
            }
        }
        for (auto i : nums){
            if(c_res_1 > 0 && i == res_1)
                ck_1++;
            if(c_res_2 > 0 && i == res_2)
                ck_2++;
        }
        if (ck_1 > length)
            result.push_back(res_1);
        if (ck_2 > length)
            result.push_back(res_2);
        return result;
    }
};

int main()
{
    Solution A;
    vector<int> num = {1,2,2,3,2,1,1,3};//{1, 2, 1, 2, 1, 3};
    for (auto i : A.majorityElement(num))
        std::cout << i << std::endl;
    return 0;
}