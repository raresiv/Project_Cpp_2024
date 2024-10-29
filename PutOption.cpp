#include "PutOption.h"

PutOption::PutOption(double e, double s) :EuropeanVanillaOption(e, s) {};

double PutOption::payoff(double z) const
{
	double payoff = 0;
	if (z <= _strike)
	{
		payoff = _strike - z;
	}
	return payoff;
}

optionType PutOption::GetOptionType() const
{
	return optionType::Put;
}

