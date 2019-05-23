#pragma once

#include <vector>
#include <stdint.h>

class PerlinNoise
{
public:
	PerlinNoise();
	PerlinNoise(uint32_t seed);
	virtual ~PerlinNoise() = default;

	double noise(double x, double y, double z) const;

protected:
	double fade(double t) const;
	double grad(int hash, double x, double y, double z) const;
	double lerp(double t, double a, double b) const;

private:
	std::vector<int32_t> _permutation;
};