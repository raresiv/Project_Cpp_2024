#pragma once
#include <cmath>
#define _USE_MATH_DEFINES
#include<iostream>
using namespace std;

class Option
{
protected:
	double _expiry;

public:
	double getExpiry();
	virtual double payoff(double)const=0;
	Option(double);

};

