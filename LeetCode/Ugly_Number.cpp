#include <iostream>

using std::cout;
using std::endl;

class Solution {
public:
    /**
     * @param num an integer
     * @return true if num is an ugly number or false
     */
    bool isUgly(int num) {
        // Write your code here
        if (num == 1)
            return true;
        if (num == 0)    
            return false;
        while(!(num & 1))
            num = num >>1;

        while(num % 3 == 0){
            num /= 3;
        }

        while(num % 5 == 0){
            num /= 5;
        }

        return num == 1;
    }
};

class Solution_another {
public:
    bool isUgly(int num) {
		for (int i = 2; i<6 && num; i++)
			while (num % i == 0)
				num /= i;
		return num == 1;
    }
};


int main()
{
    Solution A;
    std::cout << A.isUgly(2532) << std::endl;
    return 0;
}
