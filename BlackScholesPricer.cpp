#include "BlackScholesPricer.h"
#include <iostream>

double normalCDF(double x)
{
    return std::erfc(-x / std::sqrt(2)) / 2;
}

double normalPDF(double x) {
    return exp(-0.5 * x * x) / sqrt(2 * 3.1415);
}

double BlackScholesPricer::delta()
{
    if (auto* vanillaOption = dynamic_cast<EuropeanVanillaOption*>(option)) {
        double d1 = (log(asset_price / vanillaOption->_strike) + ((interest_rate + pow(volatility, 2) / 2) * vanillaOption->_expiry)) / (volatility * sqrt(vanillaOption->_expiry));
        double val_ret = 0;
        if ((*vanillaOption).GetOptionType()==optionType::Call)
        {
            val_ret = normalCDF(d1);
        }
        else {
            val_ret = normalCDF(d1) - 1;
        }
        return val_ret;
    }
    if (auto* digitalOption = dynamic_cast<EuropeanDigitalOption*>(option)) {
        double d1 = (log(asset_price / digitalOption->_strike) + ((interest_rate + pow(volatility, 2) / 2) * digitalOption->_expiry)) / (volatility * sqrt(digitalOption->_expiry));
        double d2 = d1 - volatility * sqrt(digitalOption->_expiry);

        // Calcul du Delta
        double delta = exp(-interest_rate * digitalOption->_expiry) * normalPDF(d2) / (asset_price * volatility * sqrt(digitalOption->_expiry));
        if (digitalOption->GetOptionType() == optionType::Put) {
            delta = -delta;  // Le Delta d'une option digitale put est l'opposé de celui d'une call
        }
        return delta;
    }

}


double BlackScholesPricer::operator()()
{ 
    // Disjonction de cas via dynamic_cast
    if (auto* vanillaOption = dynamic_cast<EuropeanVanillaOption*>(option)) {
        // Calcul des variables communes
        double d1 = (log(asset_price / vanillaOption->_strike) + ((interest_rate + pow(volatility, 2) / 2) * vanillaOption->_expiry)) / (volatility * sqrt(vanillaOption->_expiry));
        double d2 = d1 - (volatility * sqrt(vanillaOption->_expiry));
        if((*vanillaOption).GetOptionType()==optionType::Call){
            // Calcul pour une option call vanille
            double a = asset_price * normalCDF(d1);
            double b = vanillaOption->_strike * exp(-interest_rate * vanillaOption->_expiry) * normalCDF(d2);
            return a - b;
        }
        if((*vanillaOption).GetOptionType()==optionType::Put){
            // Calcul pour une option Put vanille
            double a = asset_price * normalCDF(-d1);
            double b = vanillaOption->_strike * exp(-interest_rate * vanillaOption->_expiry) * normalCDF(-d2);
            return b - a;
        }
    } 
    if (auto* digitalOption = dynamic_cast<EuropeanDigitalOption*>(option)) {
        // Calcul des variables communes
        double d1 = (log(asset_price / digitalOption->_strike) + ((interest_rate + pow(volatility, 2) / 2) * digitalOption->_expiry)) / (volatility * sqrt(digitalOption->_expiry));
        double d2 = d1 - (volatility * sqrt(digitalOption->_expiry));
        if((*digitalOption).GetOptionType()==optionType::Call){
            // Calcul pour une option call digitale
            return exp(-interest_rate * digitalOption->_expiry) * normalCDF(d2);
        }
        if((*digitalOption).GetOptionType()==optionType::Put){
            // Calcul pour une option put digitale
            return exp(-interest_rate * digitalOption->_expiry) * normalCDF(-d2);
        }
        
    }
}
