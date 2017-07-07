#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

class Solution {
public:
	/**
	* @param nums: a vector of integers
	* @return: an integer
	*/
	int findMissing(vector<int> &nums) {
		// write your code here
		long long target = nums.size() * (nums.size() + 1) / 2;
		for (auto i : nums)
			target -= i;
		return target;
	}
};

int main() {
	Solution A;
	vector<int> a = { 1, 2, 3, 4};
	cout << A.findMissing(a) << endl;
	system("pause");
}