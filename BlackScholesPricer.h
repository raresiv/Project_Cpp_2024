#pragma once
#include "EuropeanVanillaOption.h"
#include <cmath>
#define _USE_MATH_DEFINES

class BlackScholesPricer
{
private:
    EuropeanVanillaOption* option;
    double asset_price;
    double interest_rate;
    double volatility;

public:

    BlackScholesPricer(EuropeanVanillaOption* opt, double a_p, double i_r, double vol) : 
        option(opt), asset_price(a_p), interest_rate(i_r), volatility(vol) {}

    double operator()(const class BlackScholesPricer);

    double delta();

};

