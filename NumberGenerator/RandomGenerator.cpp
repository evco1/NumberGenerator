#include "RandomGenerator.h"

#include <random>

RandomGenerator::RandomGenerator()
{
	std::random_device rd;
	rng_.seed(rd());
}

RandomGenerator::RandomGenerator(unsigned int seed)
{
	rng_.seed(seed);
}

std::vector<int> RandomGenerator::generate(std::size_t count, int min, int max)
{
	if (max < min) std::swap(min, max);
	std::uniform_int_distribution<int> dist(min, max);
	std::vector<int> out;
	out.reserve(count);
	for (std::size_t i = 0; i < count; ++i) {
		out.push_back(dist(rng_));
	}
	return out;
}
