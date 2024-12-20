#include "AmericanCallOption.h"

AmericanCallOption::AmericanCallOption(double e, double s) :AmericanOption(e, s) {};

double AmericanCallOption::payoff(double z) const
{
	double payoff = 0;
	if (z >= _strike)
	{
		payoff = z - _strike;
	}
	return payoff;
}

/*
optionType AmericanCallOption::GetOptionType() const
{
	return optionType::Call;
}*/

