#pragma once
#include <iostream>
#include "Option.h"
#include "optionType.h"

class EuropeanDigitalOption :
    public Option
{
protected:
    double _strike;

public:
    EuropeanDigitalOption(double, double);

    virtual double payoff(double)const = 0;

    virtual optionType GetOptionType()const = 0;

    friend class BlackScholesPricer;
};

