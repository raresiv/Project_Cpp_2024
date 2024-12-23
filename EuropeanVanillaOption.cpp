#include "EuropeanVanillaOption.h"

EuropeanVanillaOption::EuropeanVanillaOption(double e, double s) : Option(e)
{
	if (s > 0)
	{
		_strike = s;	//we check that the strike price is positive
	}
	else
	{
		_strike = 0;
		cout << "strike negatif";
	}

};