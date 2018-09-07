#include "test_framework/generic_test.h"

unsigned long long ReverseBits(unsigned long long x)
{
	const short size = sizeof(long long) * 8;
	for (short i = 0; i < size >> 1; ++i)
	{
		const long long diff = ((x >> i) & 1) ^ ((x >> (size - i - 1)) & 1);
		x ^= (diff << i) | (diff << (size - i - 1));
	}
	return x;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
