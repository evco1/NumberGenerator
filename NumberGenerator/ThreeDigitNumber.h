#pragma once

#include "Number.h"
#include <string>

class ThreeDigitNumber : public Number {
public:
	// Ensures the stored value is within the three-digit range [100, 999].
	explicit ThreeDigitNumber(int value);

	std::string toString() const override;
};
