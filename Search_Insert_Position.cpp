#include <iostream>
#include <vector>
#include <assert.h>

using std::vector;
using std::cout;
using std::endl;

class Solution {
    /**
     * param A : an integer sorted array
     * param target :  an integer to be inserted
     * return : an integer
     */
public:
    int searchInsert(vector<int> &A, int target) {
        // write your code here
        int length = (int)A.size();
        int head = 0, tail = length-1, mid = 0;

        while(head <= tail)
        {
            mid = (head + tail) / 2;
            if (A[mid] < target)
                head = mid + 1;
            else if (A[mid] > target)
                tail = mid - 1;
            else{
                head = mid;
                break;
            }
        }
        return head;
    }
};

int main()
{
    Solution A;
    vector<int> _list = {1, 2};
    std::cout << A.searchInsert(_list, 0) << std::endl;
    std::cout << A.searchInsert(_list, 1) << std::endl;
    std::cout << A.searchInsert(_list, 2) << std::endl;
    std::cout << A.searchInsert(_list, 3) << std::endl;
    std::cout << A.searchInsert(_list, 4) << std::endl;
    std::cout << A.searchInsert(_list, 5) << std::endl;
    std::cout << A.searchInsert(_list, 6) << std::endl;
//    std::cout << A.searchInsert(_list, 7) << std::endl;
    return 0;
}