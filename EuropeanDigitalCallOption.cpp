#include "EuropeanDigitalCallOption.h"
EuropeanDigitalCallOption::EuropeanDigitalCallOption(double e, double s) :EuropeanDigitalOption(e, s) {};

double EuropeanDigitalCallOption::payoff(double z) const
{
	double payoff = 0;
	if (z >= _strike)
	{
		payoff = 1;
	}
	return payoff;
}


optionType EuropeanDigitalCallOption::GetOptionType() const
{
	return optionType::Call;
}
