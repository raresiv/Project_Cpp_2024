#include "AsianPutOption.h"

double AsianPutOption::payoff(double moy)const // calculate the payoff using moy
// where moy is the mean, calculate into payoffPath into AsianOption
{

	if (strike > moy) // if the strike is greater than the mean
	{
		return strike-moy; // the payoff is equal to the difference
	}
	else
	{
		return 0; // 0 else
	}
}

optionType AsianPutOption::GetOptionType()const
{
	return optionType::Put; // in order to get the type : put or call
}



AsianPutOption::AsianPutOption(const std::vector<double> vector, double s) : AsianOption(vector, s) {}; // constructor


