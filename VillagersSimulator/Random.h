#pragma once
#include <math.h>
#include <time.h>
constexpr auto RANDOM_J = 22;
constexpr auto RANDOM_K = 43;
constexpr auto RANDOM_M = 0xFFFFFFFBul; /* 2^32-5 */

//Generate random numbers
class Random
{
public:

	Random();
	Random(int seed);
	~Random();

	//
	unsigned long getSeed() const;
	//int
	unsigned long int Next();
	unsigned long int Next(int from, int to);
	//float
	float NextF(float from, float to);

private:
	void InitX(unsigned long long seed);
	//
	unsigned long m_seed; //seed
	int m_A = 69069;
	unsigned long long m_mod = RANDOM_M;
	const int m_j = RANDOM_J;
	const int m_k = RANDOM_K;
	//
	unsigned long long x[RANDOM_K];
	unsigned long m_i;
	unsigned long long m_c;
};

