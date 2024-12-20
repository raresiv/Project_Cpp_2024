#pragma once
#include "Option.h"
#include <iostream>
#include "optionType.h"
#include <vector>

using namespace std;

class AmericanOption :
    public Option
{
public:
    AmericanOption(double, double);
    bool isAmericanOption() override;
	//virtual optionType GetOptionType()const=0;


protected:
    double _strike;
};
