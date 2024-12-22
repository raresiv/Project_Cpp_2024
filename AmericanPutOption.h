#pragma once
#include "AmericanOption.h"
#include "optionType.h"
class AmericanPutOption :
    public AmericanOption
{
public:
    AmericanPutOption(double, double);
    double payoff(double)const override;
    //optionType GetOptionType()const override;
};