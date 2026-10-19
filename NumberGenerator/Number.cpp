#include "Number.h"

#include <string>
#include <sstream>

std::string Number::toString() const
{
	std::ostringstream oss;
	oss << value() << ": this number belongs to the others";
	return oss.str();
}

