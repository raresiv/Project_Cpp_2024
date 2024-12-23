#include "BlackScholesPricer.h"
#include <iostream>

// Constructor using a option pointer, an asset price, an interest rate and a volatility
BlackScholesPricer::BlackScholesPricer(Option* opt, double a_p, double i_r, double vol)
    : option(opt), asset_price(a_p), interest_rate(i_r), volatility(vol) {
}

double normalCDF(double x)
{
    return std::erfc(-x / std::sqrt(2)) / 2; // We calculate the cumulative distribution function of a N(0,1) of level x
}

double normalPDF(double x) {
    return exp(-0.5 * x * x) / sqrt(2 * 3.1415); // We calculate the probability distribution function of a N(0,1) of level x
}

double BlackScholesPricer::delta()
{
// We use dynamic cast for a case disjonction between European Vanilla and European Digital
    if (auto* vanillaOption = dynamic_cast<EuropeanVanillaOption*>(option)) {//if the option is digital
        double d1 = (log(asset_price / vanillaOption->_strike) + ((interest_rate + pow(volatility, 2) / 2) * vanillaOption->_expiry)) / (volatility * sqrt(vanillaOption->_expiry));
        double val_ret = 0;
        // We check the option type ( call or put )
        if ((*vanillaOption).GetOptionType()==optionType::Call)
        {
            val_ret = normalCDF(d1);
        }
        else {
            val_ret = normalCDF(d1) - 1;
        }
        return val_ret;
    }
    if (auto* digitalOption = dynamic_cast<EuropeanDigitalOption*>(option)) {//if the option is vanilla
        double d1 = (log(asset_price / digitalOption->_strike) + ((interest_rate + pow(volatility, 2) / 2) * digitalOption->_expiry)) / (volatility * sqrt(digitalOption->_expiry));
        double d2 = d1 - volatility * sqrt(digitalOption->_expiry);
        double delta = exp(-interest_rate * digitalOption->_expiry) * normalPDF(d2) / (asset_price * volatility * sqrt(digitalOption->_expiry));
        if (digitalOption->GetOptionType() == optionType::Put) {
            delta = -delta; // The delta of the put option is the inverse of the delta of the call option
        }
        return delta;
    }

}


double BlackScholesPricer::operator()()
{ // We use dynamic cast for a case disjonction 
    if (auto* vanillaOption = dynamic_cast<EuropeanVanillaOption*>(option)) {//If the option is vanilla
        double d1 = (log(asset_price / vanillaOption->_strike) + ((interest_rate + pow(volatility, 2) / 2) * vanillaOption->_expiry)) / (volatility * sqrt(vanillaOption->_expiry));
        double d2 = d1 - (volatility * sqrt(vanillaOption->_expiry));
        if((*vanillaOption).GetOptionType()==optionType::Call){ //If the option is a call
            double a = asset_price * normalCDF(d1);
            double b = vanillaOption->_strike * exp(-interest_rate * vanillaOption->_expiry) * normalCDF(d2);
            return a - b;
        }
        if((*vanillaOption).GetOptionType()==optionType::Put){ //If the option is a put
            double a = asset_price * normalCDF(-d1);
            double b = vanillaOption->_strike * exp(-interest_rate * vanillaOption->_expiry) * normalCDF(-d2);
            return b - a;
        }
    } 
    if (auto* digitalOption = dynamic_cast<EuropeanDigitalOption*>(option)) { //If the option is digital
        double d1 = (log(asset_price / digitalOption->_strike) + ((interest_rate + pow(volatility, 2) / 2) * digitalOption->_expiry)) / (volatility * sqrt(digitalOption->_expiry));
        double d2 = d1 - (volatility * sqrt(digitalOption->_expiry));
        if((*digitalOption).GetOptionType()==optionType::Call){ //If the option is a call
            return exp(-interest_rate * digitalOption->_expiry) * normalCDF(d2);
        }
        if((*digitalOption).GetOptionType()==optionType::Put) {//If the option is a put
            return exp(-interest_rate * digitalOption->_expiry) * normalCDF(-d2);
        }
        
    }
}
