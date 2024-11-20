#pragma once
#include <random>

class MT
{
private:

	std::mt19937 rng;
	MT(); // Le constructeur pour éviter de instanciate directly
	~MT() = default; // Le dstructeur
	// Pour éviter de copier et d'assigner
	MT(const MT&) = delete;
	MT& operator=(const MT&) = delete;

public :

	static MT& getInstance();
	static double rand_unif();
	static double rand_norm();

};

