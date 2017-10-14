#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
	int round(vector<vector<int>>& grid, int x, int y)
	{
		if (x < 0 || x > grid.size() - 1)
			return 0;
		if (y < 0 || y > grid[x].size() - 1)
			return 0;
		if (grid[x][y] == 0)
			return 0;
		grid[x][y] = 0;
		return 1 + round(grid, x+1, y) + round(grid, x-1, y) + round(grid, x, y+1) + round(grid, x, y-1);
	}

	int maxAreaOfIsland(vector<vector<int>>& grid) {
		int max = 0;
		for (int i = 0; i < grid.size(); ++i)
			for (int j = 0; j < grid[i].size(); ++j)
				if (grid[i][j] == 1)
				{
					int ar = round(grid, i, j);
					if (ar > max)
						max = ar;
				}
		return max;
	}
};

int main()
{
	Solution A;
	vector<vector<int>> a = {
		{0,0,1,0,0,0,0,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,1,0,0,0},
		{0,1,1,0,1,0,0,0,0,0,0,0,0},
		{0,1,0,0,1,1,0,0,1,0,1,0,0},
		{0,1,0,0,1,1,0,0,1,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,1,1,1,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0,0}
	};

	std::cout << A.maxAreaOfIsland(a) << std::endl;

	system("pause");
	return 0;
}

