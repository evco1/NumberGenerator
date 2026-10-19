#include "NumberStartsWithOne.h"

#include <algorithm>
#include <sstream>
#include <vector>

NumberStartsWithOne::NumberStartsWithOne(int count)
	: Number(count)
{
}

std::string NumberStartsWithOne::toString() const
{
	RandomGenerator gen;
	std::vector<int> vals = gen.generate(static_cast<std::size_t>(value()));

	std::ostringstream oss;
	oss << value() << ": starts with 1 [origin list:";
	for (std::size_t i = 0; i < vals.size(); ++i) {
		if (i) oss << ' ';
		oss << vals[i];
	}

	std::vector<int> sorted = vals;
	std::sort(sorted.begin(), sorted.end());

	oss << " Ordered list:";
	for (std::size_t i = 0; i < sorted.size(); ++i) {
		if (i) oss << ' ';
		oss << sorted[i];
	}

	oss << ']';

	return oss.str();
}
