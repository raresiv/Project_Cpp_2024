#pragma once
#include "Option.h"
#include <iostream>
#include "optionType.h"
#include <vector>

using namespace std;
using namespace std;
class AsianOption :
    public Option // derived from the option class
{
private:
	
    std::vector<double> timesteps; // the time step of our option

public:
	bool isAsianOption() override; // true if it's asian, false else
	std::vector<double> getTimeSteps(); // getter of time step
	AsianOption(std::vector<double>, double); // constructor
	double payoffPath(std::vector<double>path); // calculate the payoff using a path of S
	double strike; // strike price
};

