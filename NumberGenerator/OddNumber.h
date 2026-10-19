#pragma once

#include "Number.h"
#include <string>

class OddNumber : public Number {
public:
	// If an even value is provided, it will be adjusted to the next odd value (value + 1).
	explicit OddNumber(int value);

	// Return the number as a string and indicate it's odd.
	std::string toString() const override;
};
