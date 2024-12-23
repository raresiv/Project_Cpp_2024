#pragma once
#include "Option.h"
#include <iostream>
#include "optionType.h"
#include <vector>
using namespace std;
class AmericanOption :
    public Option // AmericanOption inherits fom Option
{
public:
    AmericanOption(double, double); // constructor which takes two double values in parameter
    bool isAmericanOption() override; // method overriding the one from Option class
    virtual optionType GetOptionType()const=0; // pure virtual method allowing the American option to be a call or put option
    double GetStrike()const; // getter for the strike value
protected:
    double _strike;
};