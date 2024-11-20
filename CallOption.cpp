#include "CallOption.h"

CallOption::CallOption(double e, double s) :EuropeanVanillaOption(e, s) {};

double CallOption::payoff(double z) const
{
	double payoff = 0;
	if (z >= _strike)
	{
		payoff = z - _strike;
	}
	return payoff;
}


optionType CallOption::GetOptionType() const
{
	return optionType::Call;
}

