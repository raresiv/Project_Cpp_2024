#include "BlackScholesPricer.h"

#include <iostream>

#include "BlackScholesPricer.h"


double normalCDF(double x)
{
    return std::erfc(-x / std::sqrt(2)) / 2;
}

double BlackScholesPricer::operator()(const BlackScholesPricer) 
{
    double a, b, c,d1,d2;
    d1 = (log(asset_price / option->_strike) + ((interest_rate + pow(volatility, 2) / 2) * option->_expiry)) / (volatility * sqrt(option->_expiry));
    d2 = (log(asset_price / option->_strike) + ((interest_rate - pow(volatility, 2) / 2) * option->_expiry)) / (volatility * sqrt(option->_expiry));
    a = asset_price * normalCDF(d1);
    b = option->_strike * exp(-interest_rate * option->_expiry) * normalCDF(d2);
    c = a - b;
    return c;

}

double BlackScholesPricer::delta()
{
    double d1 = (log(asset_price / option->_strike) + ((interest_rate + pow(volatility, 2) / 2) * option->_expiry)) / (volatility * sqrt(option->_expiry));
    double val_ret = 0;
    if ((*option).GetOptionType()==optionType::Put)
    {
        val_ret = normalCDF(d1);
    }
    else {
        val_ret = normalCDF(d1) - 1;
    }
    return val_ret;
}