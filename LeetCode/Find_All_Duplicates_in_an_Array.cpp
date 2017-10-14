#include <vector>
#include <iostream>

using std::vector;

class Solution {
public:
	inline int abs(int x)
	{
		int y = x >> 31;
		return (x^y) - y;
	}

	vector<int> findDuplicates(vector<int>& nums) {
		vector<int> res;
		int a_i = 0;
		for (auto &i : nums)
		{
			a_i = std::abs(i);
			if (nums[a_i-1] & 0x80000000)
				res.push_back(a_i);
			else
				nums[a_i-1] *= -1;
		}
		return res;
	}
};

int main()
{
	Solution A;
	vector<int> a = { 4,3,2,7,8,2,3,1 };
	for (auto &i : A.findDuplicates(a))
		std::cout << i << " ";
	system("pause");
	return 0;
}