#include "AsianOption.h"

//AsianOption::AsianOption(std::vector<double> t, double s) : Option(e)
//{
//	strike = s;
//	timesteps = t;
//	e = t.back();
//}

AsianOption::AsianOption(std::vector<double> t, double s) : Option(t.back())
{
	strike = s;
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

bool AsianOption::isAsianOption() {
	return true;
}