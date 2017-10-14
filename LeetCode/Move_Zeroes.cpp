#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
	void moveZeroes(vector<int>& nums) {
		int pos = 0;
		for (auto &i : nums)
		{
			if (i == 0)
				continue;
			nums[pos++] = i;
		}
		for (int i = pos; i < nums.size(); ++i)
			nums[i] = 0;
	}
};

int main()
{
	Solution A;
	vector<int> a = { 0, 1, 0, 3, 12 };
	A.moveZeroes(a);
	for (auto &i : a)
		std::cout << i << " ";
	system("pause");
	return 0;
}
