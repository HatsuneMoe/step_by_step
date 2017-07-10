#include <iostream>
#include <queue>
#include <vector>

using std::priority_queue;
using std::vector;
using std::cout;
using std::endl;
using std::greater;

class Solution {
public:
    /**
     * @param matrix: a matrix of integers
     * @param k: an integer
     * @return: the kth smallest number in the matrix
     */
    int kthSmallest(vector<vector<int> > &matrix, int k) {
        // write your code here
        priority_queue<int, vector<int>, greater<int>> heap;

        for(auto &i : matrix)
            for(auto &j :i)
                heap.push(j);
        while(!heap.empty()) {
            if(--k == 0)
                return heap.top();
            heap.pop();
        }
        return 0;
    }
};

int main()
{
    Solution A;

    vector<vector<int>> m;
    m.push_back(vector<int> {1, 5, 7});
    m.push_back(vector<int> {3 ,7 ,8});
    m.push_back(vector<int> {4 ,8 ,9});
    std::cout << A.kthSmallest(m, 4) << std::endl;
    return 0;
}