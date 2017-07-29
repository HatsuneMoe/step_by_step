#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
	vector<int> plusOne(vector<int>& digits) {
		bool flag = false;
		for (auto i = digits.rbegin(); i != digits.rend(); ++i)
		{
			(*i)++;
			if (*i < 10)
			{
				flag = false;
				break;
			}
				
			else
			{
				flag = true;
				*i = 0;
			}
		}
		if (flag)
		{
			digits.insert(digits.begin(), 1);
			digits[1] = 0;
		}
		return digits;
	}
};

int main()
{
	Solution A;
	vector<int> d = { 1,9,9 };
	vector<int> list = A.plusOne(d);
	for (auto i : list)
		std::cout << i << " ";
	system("pause");
	return 0;
}