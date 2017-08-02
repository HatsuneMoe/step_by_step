#include <iostream>
#include <bitset>

using std::bitset;

class Solution {
public:
	uint32_t reverseBits(uint32_t n) {
		n = (n & 0x55555555) << 1 | (n & 0xAAAAAAAA) >> 1;
		n = (n & 0x33333333) << 2 | (n & 0xCCCCCCCC) >> 2;
		n = (n & 0x0F0F0F0F) << 4 | (n & 0xF0F0F0F0) >> 4;
		n = (n & 0x00FF00FF) << 8 | (n & 0xFF00FF00) >> 8;
		n = (n & 0x0000FFFF) << 16 | (n & 0xFFFF0000) >> 16;
		return n;
	}
};

int main()
{
	Solution A;
	uint32_t a = 1234567;
	bitset<32> b = a;
	std::cout << b << std::endl;
	b = A.reverseBits(a);
	std::cout << b << std::endl;
	system("pause");
	return 0;
}