#include "EuropeanDigitalPutOption.h"

EuropeanDigitalPutOption::EuropeanDigitalPutOption(double e, double s) :EuropeanDigitalOption(e, s) {};

double EuropeanDigitalPutOption::payoff(double z) const
{
	double payoff = 0;
	if (z <= _strike)
	{
		payoff = 1;
	}
	return payoff;
}

optionType EuropeanDigitalPutOption::GetOptionType() const
{
	return optionType::Put;
}
