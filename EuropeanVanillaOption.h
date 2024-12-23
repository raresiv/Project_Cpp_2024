#pragma once
#include <iostream>
#include "optionType.h"
using namespace std;

#include "Option.h"
class EuropeanVanillaOption :
    public Option
{
protected:
    double _strike;
    
public:
    EuropeanVanillaOption(double, double);
    virtual double payoff(double)const=0;   //it is virtual so it can be overriden in the put or call options
    virtual optionType GetOptionType()const=0;  
    friend class BlackScholesPricer;
};
    



