#pragma once
#include "AsianOption.h"
class AsianPutOption :
    public AsianOption
{
public : 
		AsianPutOption(std::vector<double>, double);
		double payoff(double)const;
		optionType GetOptionType()const;
		
};	

