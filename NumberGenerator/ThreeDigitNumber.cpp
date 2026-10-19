#include "ThreeDigitNumber.h"

#include <sstream>

ThreeDigitNumber::ThreeDigitNumber(int value)
	: Number((value < 100) ? 100 : ((value > 999) ? 999 : value))
{
}

std::string ThreeDigitNumber::toString() const
{
	std::ostringstream oss;
	oss << value() << ": the digits multiplication is equal to "
		<< (value() / 100) * ((value() / 10) % 10) * (value() % 10);
	return oss.str();
}
