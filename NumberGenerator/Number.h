#pragma once

#include <string>

class Number {
public:
	explicit Number(int value) : value_(value) {}
	virtual ~Number() = default;

	// Return the stored number as a string. Can be overridden by derived classes.
	virtual std::string toString() const;

	int value() const { return value_; }

private:
	int value_;
};
