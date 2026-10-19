#pragma once

#include "Number.h"
#include "RandomGenerator.h"
#include <string>

class NumberStartsWithOne : public Number {
public:
	// 'count' is how many random numbers will be generated when toString() is called
	explicit NumberStartsWithOne(int count = 1);

	// Generate 'count' random numbers and return a string containing the original
	// sequence and the ascending-sorted sequence.
	std::string toString() const override;
};
