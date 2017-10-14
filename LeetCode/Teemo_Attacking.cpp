#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
	int findPoisonedDuration(vector<int>& timeSeries, int duration) {
		int res = 0;
		int t_sum = 0;
		if (timeSeries.size() == 0) return 0;
		if (timeSeries.size() == 1) return duration;

		for (int i=0; i<timeSeries.size()-1; ++i)
		{
			if (timeSeries[i + 1] - timeSeries[i] < duration)
			{
				t_sum += timeSeries[i + 1] - timeSeries[i];
			}
			else {
				res += t_sum + duration;
				t_sum = 0;
			}
		}

		return res + t_sum + duration;
	}
};

int main()
{
	Solution A;
	vector<int> a = { 1, 2 };
	std::cout << A.findPoisonedDuration(a, 2) << std::endl;
	system("pause");
	return 0;
}