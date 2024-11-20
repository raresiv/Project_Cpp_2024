#pragma once
#include <cmath>
#define _USE_MATH_DEFINES
#include<iostream>
using namespace std;
#include <vector>
#include <stdexcept>

class Option
{
protected:
	double _expiry;

public:
	virtual bool isAsianOption();
	double getExpiry();
	virtual double payoff(double)const=0;
	Option(double);
	virtual double payoffPath(std::vector<double> path)const;

};

