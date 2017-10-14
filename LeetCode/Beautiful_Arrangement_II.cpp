#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
	vector<int> constructArray(int n, int k) {
		vector<int> res = { 1 };
		int p = 2, q = n;
		bool f = false;
		while (k > 1)
		{
			if (f == false)
			{
				res.push_back(q--);
				k--;
			}
			else {
				res.push_back(p++);
				k--;
			}
			f = !f;
		}
		if (!f)
			for (int i = p; i <= q; ++i)
				res.push_back(i);
		else
			for (int i = q; i >= p; --i)
				res.push_back(i);

		return res;
	}
};

int main()
{
	Solution A;

	for (auto &i : A.constructArray(5, 4))
		std::cout << i << " ";

	system("pause");
	return 0;
}
