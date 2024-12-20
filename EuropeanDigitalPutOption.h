#pragma once
#include "EuropeanDigitalOption.h"
#include "optionType.h"
#include <iostream>

class EuropeanDigitalPutOption :
    public EuropeanDigitalOption
{
public:
    EuropeanDigitalPutOption(double, double);
    double payoff(double)const override;
    optionType GetOptionType()const override;
};

