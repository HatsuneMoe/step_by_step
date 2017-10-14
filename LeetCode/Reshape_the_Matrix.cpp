#include <vector>
#include <iostream>

using std::vector;

class Solution {
public:
	vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
		if (nums.size()*nums[0].size() != r*c)
			return nums;
		vector<int> flat;
		for (auto &i : nums)
			for (auto &j : i)
				flat.push_back(j);
		vector<vector<int>> res;
		auto iter = flat.begin();
		for (int _r = 0; _r < r; ++_r)
		{
			vector<int> t;
			for (int _c = 0; _c < c; ++_c)
			{
				t.push_back(*iter++);
			}
			res.push_back(t);
		}
		return res;
	}
};

int main()
{
	Solution A;
	vector<vector<int>> a = { {1,2},{3,4} };
	for (auto &i : A.matrixReshape(a, 4, 1))
	{
		for (auto &j : i)
			std::cout << j << " ";
		std::cout << std::endl;
	}
	system("pause");
	return 0;
}