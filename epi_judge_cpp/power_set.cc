#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

vector<vector<int>> GeneratePowerSet(const vector<int>& input_set)
{
	vector<vector<int>> result(1 << input_set.size());
	for (int i = 0; i < (1 << input_set.size()); ++i)
	{
		for (int j = 0; j < input_set.size(); ++j)
		{
			if (i & (1 << j))
			{
				result[i].push_back(input_set[j]);
			}
		}
	}
	return std::move(result);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"input_set"};
  return GenericTestMain(
      args, "power_set.cc", "power_set.tsv", &GeneratePowerSet,
      &UnorderedComparator<vector<vector<int>>>, param_names);
}
