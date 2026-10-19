#pragma once

#include <vector>
#include <cstddef>
#include <random>

class RandomGenerator {
public:
	RandomGenerator();
	explicit RandomGenerator(unsigned int seed);

	// Generate 'count' random integers in range [min, max]
	std::vector<int> generate(std::size_t count, int min = 0, int max = 100);

private:
	std::mt19937_64 rng_;
};
