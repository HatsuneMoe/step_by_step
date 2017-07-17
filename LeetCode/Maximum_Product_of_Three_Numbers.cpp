#include <iostream>
#include <queue>
#include <vector>

using std::vector;
using std::priority_queue;

class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        priority_queue<int> heap_max;
        priority_queue<int, vector<int>, std::greater<int>> heap_min;
        int res_max = 1;
        for (auto &i :nums){
            heap_max.push(i);
            heap_min.push(i);
        }
        int res_min = heap_max.top();
        for (int i=0; i<3; ++i){
            res_max *= heap_max.top();
            heap_max.pop();
        }
        for (int i=0; i<2; ++i){
            res_min *= heap_min.top();
            heap_min.pop();
        }
        return (res_max>res_min)? res_max:res_min;
    }
};

class Solution_lite {
public:
    int maximumProduct(vector<int>& nums) {
        int a = INT32_MIN, b = INT32_MIN, c = INT32_MIN, m = 0, n = 0;
        for (auto &i : nums){
            if (i > a){
                c = b, b = a, a = i;
            } else if (i > b) {
                c = b, b = i;
            } else if (i > c)
                c = i;
            if (i < m){
                n = m, m = i;
            } else if (i < n)
                n = i;
        }
        return std::max(a*b*c, m*n*a);
    }
};

int main()
{
    Solution_lite A;
    vector<int> a = {-1, -2, -3, 4};
    std::cout << A.maximumProduct(a) << std::endl;
    return 0;
}