#include <iostream>

class Solution {
public:
	int rangeBitwiseAnd(int m, int n) {
		int res = n;
		while (m <= res && res <= n && m < res)
			res = res & (res - 1);
		return res;
	}
};

int main()
{
	Solution A;
	std::cout << A.rangeBitwiseAnd(2, 7) << std::endl;
	system("pause");
	return 0;
}