#pragma once
#include "AsianOption.h"
class AsianCallOption :
    public AsianOption
{
public:
	AsianCallOption(std::vector<double>,double);
	double payoff(double)const;
	optionType GetOptionType()const;
	

};

