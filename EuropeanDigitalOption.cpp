#include "EuropeanDigitalOption.h"

EuropeanDigitalOption::EuropeanDigitalOption(double e, double s) : Option(e)
{
	if (s > 0)	//we check that the strike price is positive
	{
		_strike = s;
	}
	else
	{
		_strike = 0;
		cout << "strike negatif";
	}

};
