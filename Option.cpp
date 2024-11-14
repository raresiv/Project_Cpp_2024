#include "Option.h"

Option::Option(double exp) {
	if (exp > 0)
	{
		_expiry = exp;
	}
	else
	{
		cout << "expiry negatif";

	}
};

double Option::getExpiry()
{
	return _expiry;
}


