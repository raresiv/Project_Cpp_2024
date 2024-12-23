#include "PutOption.h"

PutOption::PutOption(double e, double s) :EuropeanVanillaOption(e, s) {};	// constructor

double PutOption::payoff(double z) const
{
	double payoff = 0;		// initialize the payoff to 0
	if (z <= _strike)
	{
		payoff = _strike - z;	// we exercice if the price is < than the strike
	}
	return payoff;	// else the payoff will be 0 because we do not exercice
}

optionType PutOption::GetOptionType() const
{
	return optionType::Put;	//option type is specified
}

