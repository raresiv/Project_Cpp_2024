#pragma once
#include "AsianOption.h"
class AsianCallOption :
    public AsianOption
{
public:
	AsianCallOption(double,double, std::vector<double>);
	double payoff(double)const;
	optionType GetOptionType()const;
	

};

