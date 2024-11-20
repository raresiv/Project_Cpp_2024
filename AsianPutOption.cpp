#include "AsianPutOption.h"

double AsianPutOption::payoff(double moy)const
{

	if (strike > moy)
	{
		return strike-moy;
	}
	else
	{
		return 0;
	}
}

optionType AsianPutOption::GetOptionType()const
{
	return optionType::Put;
}

