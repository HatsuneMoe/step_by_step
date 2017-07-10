#include <iostream>

using std::cout;
using std::endl;


class Solution{
public:
    /**
     * @param n: an integer
     * @return an integer f(n)
     */
    int fibonacci(int n) {
        // write your code here
        int res[2][2] = {1, 0, 0, 1};
        int a[2][2] = {1, 1, 1, 0};
        int tmp[2][2];

        for (auto i=n; i; i=i>>1){
            if (i & 1){
                tmp[0][0] = res[0][0];
                tmp[1][0] = res[1][0];
                tmp[0][1] = res[0][1];
                tmp[1][1] = res[1][1];

                res[0][0] = tmp[0][0] * a[0][0] + tmp[0][1] * a[1][0];
                res[0][1] = tmp[0][0] * a[0][1] + tmp[0][1] * a[1][1];

                res[1][0] = tmp[1][0] * a[0][0] + tmp[1][1] * a[1][0];
                res[1][1] = tmp[1][0] * a[0][1] + tmp[1][1] * a[1][1];
            }
            tmp[0][0] = a[0][0];
            tmp[1][0] = a[1][0];
            tmp[0][1] = a[0][1];
            tmp[1][1] = a[1][1];

            a[0][0] = tmp[0][0] * tmp[0][0] + tmp[0][1] * tmp[1][0];
            a[0][1] = tmp[0][0] * tmp[0][1] + tmp[0][1] * tmp[1][1];

            a[1][0] = tmp[1][0] * tmp[0][0] + tmp[1][1] * tmp[1][0];
            a[1][1] = tmp[1][0] * tmp[0][1] + tmp[1][1] * tmp[1][1];
        }
        return res[0][0];
    }
};


int main()
{
    Solution A;
    cout << A.fibonacci(0) << endl;
    cout << A.fibonacci(1) << endl;
    cout << A.fibonacci(2) << endl;
    cout << A.fibonacci(3) << endl;
    cout << A.fibonacci(4) << endl;
    cout << A.fibonacci(5) << endl;
    cout << A.fibonacci(6) << endl;
    cout << A.fibonacci(7) << endl;
    cout << A.fibonacci(8) << endl;
    cout << A.fibonacci(9) << endl;
    return 0;
}