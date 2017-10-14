#include <queue>
#include <vector>
#include <iostream>
#include <functional>

using std::vector;
using std::priority_queue;

class Solution {
public:
	int arrayPairSum(vector<int>& nums) {
		int sum = 0;
		priority_queue<int, vector<int>, std::greater<int>> tree;
		for (auto &i : nums)
			tree.push(i);
		for (int i = 0; i < nums.size() - 1; i += 2)
		{
			sum += tree.top();
			tree.pop();
			tree.pop();
		}
		return sum;
	}
};

int main()
{
	Solution A;
	vector<int> a = { 1, 4, 3, 2 };
	std::cout << A.arrayPairSum(a) << std::endl;
	system("pause");
	return 0;
}