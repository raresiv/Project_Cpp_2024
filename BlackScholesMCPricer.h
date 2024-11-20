#pragma once
#include "Option.h"
class BlackScholesMCPricer
{
private:
	int nb_paths;
	Option* option;
	double initial_price;
	double initerest_rate;
	double volatility;
public:
	BlackScholesMCPricer(Option* option, double initial_price, double initerest_rate, double volatility);
	int getNbPaths();
	void generate(int nb_paths)
};

