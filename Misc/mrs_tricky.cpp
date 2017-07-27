#include <iostream>
#include <bitset>

using std::bitset;

#if (!defined _WIN64) && (!defined _X86_64_)
int abs(int i)
{
	/*
	 * when i >= 0, t = 0, so (i^t) means i.
	 * when i < 0, t = -1(0xFFFFFFFF), (i^t)-t = ~i + 1 = -i
	 */
	int t = i >> 31;
	return (i ^ t) - t;
}

int nm_sqrt(unsigned x)
{
	/*
	 * newton method, f(x) = x^2 - input, f'(x) = 2x
	 * x_n+1 = (x_n + input / x_n) / 2
	 * guess g0 for init
	 * do while approximations
	 */
	unsigned x1;
	int s, g0, g1;

	if (x <= 1)
		return x;
	s = 1;
	x1 = x - 1;
	if (x1 > 0xFFFF){ s += 8; x1 >>= 16; }
	if (x1 > 0xFF) { s += 4; x1 >>= 8; }
	if (x1 > 0xF) { s += 2; x1 >>= 4; }
	if (x1 > 0x3) s += 1;

	g0 = 1 << s; // guess g0
	g1 = (g0 + (x >> s)) >> 1; // init 

	while (g1 < g0) // approximations
	{
		g0 = g1;
		g1 = (g0 + (x / g0)) >> 1;
	}
	return g0;
}
#else 
int abs(int i)
{
	int t = i >> 63;
	return (i ^ t) - t;
}

int nm_sqrt(unsigned x)
{
	unsigned x1;
	int s, g0, g1;

	if (x <= 1)
		return x;
	s = 1;
	x1 = x - 1;
	if (x1 > 0xFFFFFFFF) { s += 16; x1 >>= 32; }
	if (x1 > 0xFFFF) { s += 8; x1 >>= 16; }
	if (x1 > 0xFF) { s += 4; x1 >>= 8; }
	if (x1 > 0xF) { s += 2; x1 >>= 4; }
	if (x1 > 0x3) s += 1;

	g0 = 1 << s; // guess g0
	g1 = (g0 + (x >> s)) >> 1; // init 

	while (g1 < g0) // approximations
	{
		g0 = g1;
		g1 = (g0 + (x / g0)) >> 1;
	}
	return g0;
}
#endif 

int sign(int i)
{
	return (i > 0) - (i < 0);
}

int mean_floor(int x, int y)
{
	/*
	 * part1: x&y part2 x^y
	 * (x & y) is same
	 * x^y is a sum of different bits ,mean is (x^y) >> 1
	 */
	return (x & y) + ((x^y) >> 1);
}

int mean_ceil(int x, int y)
{
	return (x | y) - ((x^y) >> 1);
}

int main()
{
	//bitset<64> a = ~(-3);
	//std::cout << a << std::endl;
	std::cout << "" << std::endl;
	system("pause");
	return 0;
}