#include "test_framework/generic_test.h"

unsigned long long ClosestIntSameBitCount(unsigned long long x)
{
	assert(x && ~x);

	// y will have 1s in position i where i-th and (i + 1)-th bits of x are different
	unsigned long long y = x ^ (x >> 1);
	// in y leave only the lowest 1 (the smallest i)
	y &= ~(y - 1);
	// in x swap i-th and (i + 1)-th bits
	return x ^ y ^ (y << 1);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "closest_int_same_weight.cc",
                         "closest_int_same_weight.tsv", &ClosestIntSameBitCount,
                         DefaultComparator{}, param_names);
}
