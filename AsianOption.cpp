#include "AsianOption.h"

//AsianOption::AsianOption(std::vector<double> t, double s) : Option(e)
//{
//	strike = s;
//	timesteps = t;
//	e = t.back();
//}

AsianOption::AsianOption(std::vector<double> t, double s) : Option(t.back()) // constructor
{ // where the expiry is the last element of our timestep
	strike = s;
	timesteps = t;
}

double AsianOption::payoffPath(std::vector<double>path) // calculate the payoff with a path
{
	double h = 0; // initialization of the h (like in the subject of the project) to 0
	for (int i = 0; i < path.size(); i++) // adding to h each value of the path, these is the S in the subject
	{
		h += path[i];
	}
	h = h / path.size(); // doing the mean of it

	return payoff(h); // calculate the payoff of the option depending if its a call or put
}

std::vector<double> AsianOption::getTimeSteps()
{
	return timesteps; // getting the timestep
}

bool AsianOption::isAsianOption() {
	return true; // if the option is asian
}