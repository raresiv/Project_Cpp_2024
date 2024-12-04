#pragma once
#include "Option.h"
#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalOption.h"
#include <cmath>
#define _USE_MATH_DEFINES

class BlackScholesPricer
{
private:
    Option* option;
    double asset_price;
    double interest_rate;
    double volatility;

public:

    BlackScholesPricer(Option* opt, double a_p, double i_r, double vol) : 
        option(opt), asset_price(a_p), interest_rate(i_r), volatility(vol) {}

    double operator()();

    double delta();

};

