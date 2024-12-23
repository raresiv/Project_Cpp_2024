#include "Option.h"

Option::Option(double exp) {
	if (exp > 0)	//we verify that the expiry is positive
	{
		_expiry = exp;
	}
	else
	{
		cout << "expiry negatif";

	}
};

//function returning the expiry which is private
double Option::getExpiry()
{
	return _expiry;
}

bool Option::isAsianOption() { //function checking if the Option is Asian
	return false;
}


bool Option::isAmericanOption() {	//function checking if the Option is American
    return false;
}

double Option::payoffPath(std::vector<double> path)const
{
	return payoff(path.back());	//return the last value of the payoff path for the asian options
}


