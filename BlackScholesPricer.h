#pragma once
#include "Option.h"
#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalOption.h"
#include <cmath>
#define _USE_MATH_DEFINES

class BlackScholesPricer
{
private:
    Option* option; // We use a pointer in order use the pricer on different types of options
    double asset_price;
    double interest_rate;
    double volatility;

public:
    BlackScholesPricer(Option* opt, double a_p, double i_r, double vol);
    double operator()();
    double delta();
};

