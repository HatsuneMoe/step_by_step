#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
	bool canJump(vector<int>& nums) {
		int can_jmp = 0;
		for (auto i = nums.begin(); i != nums.end(); ++i)
		{
			if (*i > can_jmp)
				can_jmp = *i;
			if (can_jmp == 0 && i != nums.end() - 1)
				return false;
			can_jmp--;
		}

		return true;
	}
};

int main()
{
	Solution A;
	std::cout << A.canJump(vector<int> {0}) << std::endl;
	system("pause");
	return 0;
}