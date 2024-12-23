#pragma once
#include <random>

class MT
{
private:

	std::mt19937 rng;
	MT(); // constructor to prevent direct instantiation
	~MT() = default; // destructeur
	// To prevent copying and assigning 
	MT(const MT&) = delete; // delete the copy constructor 
	MT& operator=(const MT&) = delete; // delete copy assignment operator

public :

	static MT& getInstance();
	static double rand_unif();
	static double rand_norm();

};

