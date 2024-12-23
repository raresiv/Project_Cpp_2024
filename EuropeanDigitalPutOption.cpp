#include "EuropeanDigitalPutOption.h"

EuropeanDigitalPutOption::EuropeanDigitalPutOption(double e, double s) :EuropeanDigitalOption(e, s) {};	//constructor

double EuropeanDigitalPutOption::payoff(double z) const
{
	double payoff = 0;	//we set the payoff at 0
	if (z <= _strike)
	{
		payoff = 1;	//if the price z is < to the strike price the option is executed and the payoff is 1
	}
	return payoff; //else the payoff is 0
}

optionType EuropeanDigitalPutOption::GetOptionType() const
{
	return optionType::Put;	// we specify the option type
}
