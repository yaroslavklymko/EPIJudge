#include "test_framework/generic_test.h"

short CountBits(unsigned int x)
{
	/* naive solution
	short result = 0;
	while (x)
	{
		result += x & 1;
		x >>= 1;
	}

	return result;*/

	// Hamming weight solution
	x -= (x >> 1) & 0x5555555555555555;             //put count of each 2 bits into those 2 bits
	x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333); //put count of each 4 bits into those 4 bits 
	x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0f;        //put count of each 8 bits into those 8 bits 
	return (x * 0x0101010101010101) >> 56;  //returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "count_bits.cc", "count_bits.tsv", &CountBits,
                         DefaultComparator{}, param_names);
}
