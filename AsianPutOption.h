#pragma once
#include "AsianOption.h"
class AsianPutOption :
    public AsianOption
{
public : 
		AsianPutOption(double, std::vector<double>);
		double payoff(double)const;
		optionType GetOptionType()const;
		double strike;
};	

