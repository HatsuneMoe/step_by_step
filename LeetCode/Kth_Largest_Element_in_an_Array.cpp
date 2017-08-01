#include <iostream>
#include <queue>
#include <vector>

using std::priority_queue;
using std::vector;

class Solution {
public:
	int findKthLargest(vector<int>& nums, int k) {
		priority_queue<int> heap;
		for (auto &i : nums)
			heap.push(i);
		while (!heap.empty()) {
			if (--k == 0)
				return heap.top();
			heap.pop();
		}
	}
};

int main()
{
	Solution A;

	vector<int> m = { 3,2,1,5,6,4 };
	std::cout << A.findKthLargest(m, 2) << std::endl;
	system("pause");
	return 0;
}