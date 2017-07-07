#include <iostream>

using std::endl;
using std::cout;

class Solution {
public:
    /**
     * @param x the base number
     * @param n the power number
     * @return the result
     */
    double myPow(double x, int n) {
        // Write your code here
        bool is_pos = true;
        unsigned int unsig_n = (unsigned int)n;
        double result = 1;
        if(n < 0){
            is_pos = false;
            unsig_n = (unsigned int)-n;
        }
        for(auto i=unsig_n; i; i>>=1){
            if(i & 1)
                result = x * result;
            x = x * x;
        }
        return (is_pos)?result:1/result;
    }
};

int main()
{
    Solution A;
    std::cout << A.myPow(1, -2147483647) << std::endl;
    return 0;
}