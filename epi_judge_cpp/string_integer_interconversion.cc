#include <string>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(long long int x)
{
	string result;
	const bool neg = (x < 0);
	x = (x < 0) ? -x : x;

	do 
	{
		result += '0' + (x % 10);
		x /= 10;
	}
	while (x);

	if (neg)
	{
		result += '-';
	}

	std::reverse(result.begin(), result.end());
	return std::move(result);
}

long long int StringToInt(const string& s)
{
	long long int result = 0;
	bool neg = false;

	for (size_t i = 0; i < s.size(); ++i)
	{
		if (i == 0 && s[i] == '-')
		{
			neg = true;
			continue;
		}
		if (s[i] < '0' || s[i] >'9')
		{
			throw std::exception(s.c_str());
		}
		result *= 10;
		result += s[i] - '0';
	}
	return neg  ? -result : result;
}

void Wrapper(int x, const string& s) {
  if (IntToString(x) != s) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
