#pragma once
#include "AmericanOption.h"
#include "optionType.h"
class AmericanCallOption :
    public AmericanOption
{
public:
    AmericanCallOption(double, double);
    double payoff(double)const override;
    optionType GetOptionType()const override;
};