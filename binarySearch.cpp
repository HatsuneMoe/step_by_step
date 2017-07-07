#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;


class Solution {
public:
    /**
     * @param nums: The integer array.
     * @param target: Target number to find.
     * @return: The first position of target. Position starts from 0.
     */
    int binarySearch(vector<int> &array, int target) {
        // write your code here
        int head = 0, tail = (int)array.size() - 1;
        int mid;
        while(head <= tail){
            mid = head + (tail - head) / 2;
            if (array[mid] > target)
                tail = mid - 1;
            else if (array[mid] < target)
                head = mid + 1;
            else {
                while(mid > 0 && array[mid-1] == target)
                    mid--;
                return mid;
            }
        }

        return -1;
    }
};

int main()
{
    Solution A;
    vector<int> _list = {3,4,5,8,8,8,8,10,13,14};
    std::cout << A.binarySearch(_list, 8) << std::endl;
    return 0;
}