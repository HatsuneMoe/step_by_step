#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
	vector<int> grayCode(int n) {
		vector<int> res;
		res.push_back(0);
		for (auto i = 1; i <= (1 << n) - 1; ++i)
			res.push_back(i ^ (i >> 1));
		return res;
	}
};

int main()
{
	Solution A;

	for (auto i : A.grayCode(0))
	{
		std::cout << i << std::endl;
	}

	system("pause");
	return 0;
}