#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
	void sortColors(vector<int>& nums) {
		int count[3] = { 0 };
		for (auto &i : nums)
			count[i]++;
		for (auto &i : nums)
		{
			if (count[0] > 0)
			{
				i = 0;
				count[0]--;
			}
			else if (count[1] > 0)
			{
				i = 1;
				count[1]--;
			}
			else if (count[2] > 0)
			{
				i = 2;
				count[2]--;
			}
		}
	}
};

int main()
{
	Solution A;
	vector<int> a = {1, 0, 2, 1, 2};
	A.sortColors(a);
	for (auto i : a)
		std::cout << i << std::endl;
	system("pause");
	return 0;
}