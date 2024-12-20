#pragma once
#include "Option.h"
class BlackScholesMCPricer
{
private:
	int nb_generate;
	Option* option;
	double initial_price;
	double initerest_rate;
	double volatility;
	double curent_estimate_price;
	double sum_payoff;
	double sum_payoff_carre;
public:
	BlackScholesMCPricer(Option* option, double initial_price, double initerest_rate, double volatility);
	int getNbPaths();
	void generate(int nb_paths);
	double operator() ();
	std::vector<double> confidenceInterval();
};

