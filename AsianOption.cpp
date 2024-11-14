#include "AsianOption.h"

AsianOption::AsianOption(double e,std::vector<double> t) : Option(e)
{
	timesteps = t;
}

double AsianOption::payoffPath(std::vector<double>path)
{
	double h = 0;
	for (int i = 0; i < path.size(); i++)
	{
		h += path[i];
	}
	h = h / path.size();

	return payoff(h);
}

std::vector<double> AsianOption::getTimeSteps()
{
	return timesteps;
}