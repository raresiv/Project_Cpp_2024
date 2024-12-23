#include "AmericanPutOption.h"
AmericanPutOption::AmericanPutOption(double e, double s) :AmericanOption(e, s) {};	//constructor using the constructor of the AmericanOption
double AmericanPutOption::payoff(double z) const
{
	double payoff = 0;	//we set the payoff at 0
	if (z <= _strike)
	{
		payoff = _strike - z;	//if the price z is <= to the strike price the option is executed and the payoff is 1
	}
	return payoff;  //else the payoff is 0
}

optionType AmericanPutOption::GetOptionType() const
{
	return optionType::Put;	// we specify the option type
}
