#include <iostream>

#if (!defined _WIN64) && (!defined _X86_64_)
//int count_bits_1_num(int a)
//{
//	a = ((a & 0xAAAAAAAA) >> 1) + (a & 0x55555555);
//	a = ((a & 0xCCCCCCCC) >> 2) + (a & 0x33333333);
//	a = ((a & 0xF0F0F0F0) >> 4) + (a & 0x0F0F0F0F);
//	a = ((a & 0xFF00FF00) >> 8) + (a & 0x00FF00FF);
//	a = ((a & 0xFFFF0000) >> 16) + (a & 0x0000FFFF);
//	return a;
//}

int count_bits_1_num_sp(int a)
{
	a = ((a & 0xAAAAAAAA) >> 1) + (a & 0x55555555);
	a = ((a & 0xCCCCCCCC) >> 2) + (a & 0x33333333);
	a = ((a & 0xF0F0F0F0) >> 4) + (a & 0x0F0F0F0F);
	a = ((a & 0xFF00FF00) >> 8) + a;
	a = ((a & 0xFFFF0000) >> 16) + a;
	return a & 0x3F;
}
#else  
int count_bits_1_num_sp(int a)
{
	a = ((a & 0xAAAAAAAAAAAAAAAA) >> 1) + (a & 0x5555555555555555);
	a = ((a & 0xCCCCCCCCCCCCCCCC) >> 2) + (a & 0x3333333333333333);
	a = ((a >> 4) + a)  & 0x0F0F0F0F0F0F0F0F;
	a = ((a & 0xFF00FF00FF00FF00) >> 8) + a;
	a = ((a & 0xFFFF0000FFFF0000) >> 16) + a;
	a = ((a & 0xFFFFFFFF00000000) >> 32) + a;
	return a & 0x7F;
}
#endif 

class Solution {
public:
	int hammingWeight(uint32_t n) {
	#if (!defined _WIN64) && (!defined _X86_64_)
		n = ((n & 0xAAAAAAAA) >> 1) + (n & 0x55555555);
		n = ((n & 0xCCCCCCCC) >> 2) + (n & 0x33333333);
		n = ((n & 0xF0F0F0F0) >> 4) + (n & 0x0F0F0F0F);
		n = ((n & 0xFF00FF00) >> 8) + n;
		n = ((n & 0xFFFF0000) >> 16) + n;
		return n & 0x3F;
	#else  
		n = ((n & 0xAAAAAAAAAAAAAAAA) >> 1) + (n & 0x5555555555555555);
		n = ((n & 0xCCCCCCCCCCCCCCCC) >> 2) + (n & 0x3333333333333333);
		n = ((n >> 4) + n) & 0x0F0F0F0F0F0F0F0F;
		n = ((n & 0xFF00FF00FF00FF00) >> 8) + n;
		n = ((n & 0xFFFF0000FFFF0000) >> 16) + n;
		n = ((n & 0xFFFFFFFF00000000) >> 32) + n;
		return n & 0x7F;
	#endif 
	}
};



int main()
{
	std::cout << count_bits_1_num_sp(0xf1f3ffffff) << std::endl;
	system("pause");
	return 0;
}