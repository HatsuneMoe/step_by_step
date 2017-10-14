#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
	vector<int> productExceptSelf(vector<int>& nums) {
		vector<int> res(nums.size(), 1);
		int t = nums[res.size() - 1];
		for (int i = res.size() - 2; i >= 0; --i)
		{
			res[i] = t;
			t *= nums[i];
		}
		t = 1;
		for (int i = 0; i < nums.size(); ++i)
		{
			res[i] *= (i >= 1) ? t : 1;
			t *= nums[i];
		}

		return res;
	}
};

int main()
{
	Solution A;
	vector<int> a = { 1,2,3,4 };
	for (auto &i : A.productExceptSelf(a))
		std::cout << i << " ";
	system("pause");
	return 0;
}