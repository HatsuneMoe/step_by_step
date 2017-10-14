#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
	inline int abs(int n)
	{
		int y = n >> 31;
		return (n ^ y) - y;
	}

	vector<int> findDisappearedNumbers(vector<int>& nums) {
		vector<int> res;
		for (auto &i : nums)
		{
			int _t = abs(i) - 1;
			nums[_t] = nums[_t] > 0 ? -nums[_t] : nums[_t];
		}
		for (int i=0;i<nums.size();++i)
			if (nums[i] > 0)
				res.push_back(i+1);
		return res;
	}
};

int main()
{
	Solution A;
	vector<int> a = { 4,3,2,7,8,2,3,1 };
	for (auto &i : A.findDisappearedNumbers(a))
		std::cout << i << " ";
	
	system("pause");
	return 0;
}
