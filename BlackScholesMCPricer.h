#pragma once
#include "Option.h"
class BlackScholesMCPricer
{
private:
	int nb_generate;// nbr of path that will be generate during the lifetime of the calculus of the option
	Option* option; // the option
	double initial_price; // initiale price
	double initerest_rate; // the interest rate
	double volatility; // volatility
	double curent_estimate_price; // the current estimate of the price using MC method
	double sum_payoff; // these two sum will be use in order to have the IC
	double sum_payoff_carre;
public:
	BlackScholesMCPricer(Option* option, double initial_price, double initerest_rate, double volatility); // constructor
	int getNbPaths();
	void generate(int nb_paths);
	double operator() ();
	std::vector<double> confidenceInterval();
};

