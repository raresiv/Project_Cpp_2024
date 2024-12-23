#include "MT.h"

MT::MT() : rng(std::random_device{}()) {} // we initialize the random nb generator rng

MT& MT::getInstance() {
	static MT instance; // create a unique inatance of MT
	return instance;
}

double MT::rand_unif()
{
	std::uniform_real_distribution<double> dist(0.0, 1.0); // we define a unifomr distribution on the interval [0,1]
	return dist(getInstance().rng); // it generates a uniforme random number using the instance's random generator
}

double MT::rand_norm()
{
	std::normal_distribution<double> dist(0.0, 1.0); // we define a normal distribution with mean 0 and standard deviation 1
	return dist(getInstance().rng); // it generates a normal random number using the instance's random generator
}