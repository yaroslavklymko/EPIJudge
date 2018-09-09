#include <string>
#include "test_framework/generic_test.h"
using std::string;

string ConvertBase(const string& num_as_string, int b1, int b2)
{
	auto chToNum = [] (const char ch, const int base)
	{
		int result = 16;
		if ('0' <= ch && ch <= '9')
			result = ch - '0';
		if ('A' <= ch && ch <= 'F')
			result = 10 + ch - 'A';
		assert(result < base && base <= 16);
		return result;
	};

	auto numToCh = [](const int num, const int base)
	{
		assert(0 <= num && num < base && base <= 16);
		if (num <= 9)
			return '0' + num;
		else
			return 'A' + num - 10;
	};

	bool neg = false;
	int num = 0;
	for (int i = 0; i < num_as_string.size(); ++i)
	{
		if (i == 0 && num_as_string[i] == '-')
		{
			neg = true;
			continue;
		}

		const int dig = chToNum(num_as_string[i], b1);
		num *= b1;
		num += dig;
	}

	string result;
	do 
	{
		result += numToCh(num % b2, b2);
		num /= b2;
	}
	while (num);

	if (neg)
	{
		result += '-';
	}

	std::reverse(result.begin(), result.end());
	return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
