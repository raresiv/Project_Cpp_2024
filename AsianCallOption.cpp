#include "AsianCallOption.h"

double AsianCallOption::payoff(double moy)const
{
	
	if (moy>strike)
	{
		return moy-strike;
	}
	else
	{
		return 0;
	}
}

optionType AsianCallOption::GetOptionType()const
{
	return optionType::Call;
}


AsianCallOption::AsianCallOption(double value,double s, const std::vector<double> vector) : AsianOption(value,s, vector) {};

