#include "AsianCallOption.h"

double AsianCallOption::payoff(double moy)const // calculate the payoff using moy
// where moy is the mean, calculate into payoffPath into AsianOption
{
	
	if (moy>strike) // if the mean is greater than the strike
	{ // we "exerce" the option and
		return moy-strike; // we get mean minus the strike
	}
	else
	{
		return 0; // 0 else
	}
}

optionType AsianCallOption::GetOptionType()const
{
	return optionType::Call; // in order to get the type : put or call
}


AsianCallOption::AsianCallOption(const std::vector<double> vector, double s) : AsianOption(vector, s) {}; // constructor

