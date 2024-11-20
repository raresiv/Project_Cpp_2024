#pragma once
#include "Option.h"
#include <iostream>
#include "optionType.h"
#include <vector>

using namespace std;
using namespace std;
class AsianOption :
    public Option
{
private:
	
    std::vector<double> timesteps;

public:
	bool isAsianOption() override;
	std::vector<double> getTimeSteps();
	AsianOption(double,double,std::vector<double>);
	double payoffPath(std::vector<double>path);
	double strike;
};

