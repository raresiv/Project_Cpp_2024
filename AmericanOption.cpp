#include "AmericanOption.h"
AmericanOption::AmericanOption(double e, double s) : Option(e) // constructor initialized with the expiry from option and a strike price given in parameter
{
	// checking if the strike price is positive
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
bool AmericanOption::isAmericanOption() { // method helping to consider the option as an American option
	return true; 
}

double AmericanOption::GetStrike()const { // getter returning the strike price
	return _strike;
}