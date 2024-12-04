#pragma once
#include "EuropeanDigitalOption.h"
#include "optionType.h"
#include <iostream>
class EuropeanDigitalCallOption :
    public EuropeanDigitalOption
{    
public:
    EuropeanDigitalCallOption(double, double);
    double payoff(double)const override;
    optionType GetOptionType()const override;

};

