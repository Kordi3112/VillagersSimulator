#include "Random.h"

Random::Random()
{
	unsigned long time0 = time(0);
	InitX(time0);
	m_seed = time0;
}

Random::Random(int seed)
{
	InitX(seed);
	m_seed = seed;
}

Random::~Random()
{
}

unsigned long Random::getSeed() const
{
	return m_seed;
}

unsigned long int Random::Next()
{
	//http://www.algorytm.org/liczby-pseudolosowe/generator-swbg-generator-odejmowanie-z-pozyczka.html

	unsigned long long result;

	if (x[(m_k + m_i - m_j) % m_k] >= x[m_i] + m_c)
	{
		x[m_i] = x[(m_k + m_i - m_j) % m_k] - x[m_i] - m_c;
		m_c = 0;
	}
	else
	{
		x[m_i] = m_mod - ((x[m_i] + m_c) - x[(m_k + m_i - m_j) % m_k]);
		m_c = 1;
	}

	result = x[m_i];
	m_i = (m_i + 1) % m_k;

	return abs(result);

}

unsigned long int Random::Next(int from, int to)
{
	return abs(Next() % (to - from + 1) + from);
}

float Random::NextF(float from, float to)
{
	return 2* static_cast<float>(Next()) / RANDOM_M * (to - from) + from;
}

void Random::InitX(unsigned long long seed)
{
	x[0] = seed;
	for (int j = 1; j < m_k; j++)
		x[j] = (m_A * x[j - 1]) % m_mod;

	m_i = 0;
	m_c = 0;
}
