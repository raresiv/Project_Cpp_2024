#include "MT.h"

MT::MT() : rng(std::random_device{}()) {}

MT& MT::getInstance() {
	static MT instance;
	return instance;
}

double MT::rand_unif()
{
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	return dist(getInstance().rng);
}

double MT::rand_unif()
{
	std::normal_distribution<double> dist(0.0, 1.0);
	return dist(getInstance().rng);
}