#include "OddNumber.h"

#include <sstream>

OddNumber::OddNumber(int value)
	: Number((value % 2 == 0) ? (value + 1) : value)
{
}

std::string OddNumber::toString() const
{
	std::ostringstream oss;
	oss << value() << ": this is an odd number";
	return oss.str();
}
