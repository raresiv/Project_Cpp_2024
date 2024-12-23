#include "CallOption.h"

CallOption::CallOption(double e, double s) :EuropeanVanillaOption(e, s) {};	// constructor using the constructor of a European option

double CallOption::payoff(double z) const	// calculates the payoff
{
	double payoff = 0;
	if (z >= _strike)	// if the price is greater than the strike, we exerce the option
	{
		payoff = z - _strike;
	}
	return payoff;	// else it's 0 because we don't exerce it
}


optionType CallOption::GetOptionType() const
{
	return optionType::Call;	//we specify the type of the option
}

