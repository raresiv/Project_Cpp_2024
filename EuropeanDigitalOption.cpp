#include "EuropeanDigitalOption.h"

EuropeanDigitalOption::EuropeanDigitalOption(double e, double s) : Option(e)
{
	if (s > 0)
	{
		_strike = s;
	}
	else
	{
		_strike = 0;
		cout << "strike negatif";
	}

};
