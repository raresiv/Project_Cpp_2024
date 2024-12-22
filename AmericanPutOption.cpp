#include "AmericanPutOption.h"
AmericanPutOption::AmericanPutOption(double e, double s) :AmericanOption(e, s) {};
double AmericanPutOption::payoff(double z) const
{
	double payoff = 0;
	if (z <= _strike)
	{
		payoff = _strike - z;
	}
	return payoff;
}
/*
optionType AmericanPutOption::GetOptionType() const
{
	return optionType::Put;
}
*/