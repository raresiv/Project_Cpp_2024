#include "EuropeanDigitalCallOption.h"
EuropeanDigitalCallOption::EuropeanDigitalCallOption(double e, double s) :EuropeanDigitalOption(e, s) {};//constructor

double EuropeanDigitalCallOption::payoff(double z) const
{
	double payoff = 0; //we set the payoff at 0
	if (z >= _strike)
	{
		payoff = 1;	//if the price z is > to the strike price the option is executed and the payoff is 1
	}
	return payoff;	//else the payoff is 0
}


optionType EuropeanDigitalCallOption::GetOptionType() const
{
	return optionType::Call;	// we specify the option type
}
