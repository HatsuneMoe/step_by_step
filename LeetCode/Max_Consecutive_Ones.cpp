#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
	int findMaxConsecutiveOnes(vector<int>& nums) {
		int max = 0;
		int sum = 0;
		for (auto &i : nums)
		{
			if (i == 1)
			{
				sum++;
			}	
			else
			{
				if (max < sum)
				{
					max = sum;
				}
				sum = 0;
			}
		}
		return max;
	}
};

int main()
{
	Solution A;
	vector<int> a = { 1,1,1,1,0,1,1,1 };
	std::cout << A.findMaxConsecutiveOnes(a) << std::endl;
	system("pause");
	return 0;
}