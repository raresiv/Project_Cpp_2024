#include "BlackScholesMCPricer.h"
#include "MT.h"
#include "AsianOption.h"
#include <stdexcept>


BlackScholesMCPricer::BlackScholesMCPricer(Option* opt, double ip, double ir, double vol){
	option = opt;
	initial_price = ip;
	initerest_rate = ir;
	volatility = vol;
	nb_generate = 0;
	sum_payoff_carre = 0; // we use these variable as in the TD
	sum_payoff = 0; // and this one too in order 
	curent_estimate_price = 0;
};

int BlackScholesMCPricer::getNbPaths() {
	return nb_generate; // return the number of path
}

void BlackScholesMCPricer::generate(int nb_paths) {
	double expiry = option->getExpiry(); // we get the expiry
	double const_exposant = initerest_rate - (pow(volatility,2) / 2);  // in order to simplify the calculus
	// we had a constante that we will use in every calculus of price
	double s = initial_price; // getting the initiale price
	nb_generate = nb_generate + nb_paths; //  adding the nbr of new path into our variable path
	for (int i = 0; i < nb_paths; i++) { // for every path we do a simulation
		s = initial_price;
		if (option->isAsianOption() == true) { // if the option is anian we use a different formula
			
			AsianOption* asian_option = dynamic_cast<AsianOption*>(option); // we "transform" it into asian option in order
			// to have access to its atrributs
			std::vector<double> timesteps = asian_option->getTimeSteps(); // we get the time steps
			std::vector<double> S_vect; // and in initialize a vector
			for (int j = 0;j < timesteps.size(); j++) {
				double Z = MT::rand_norm(); // random generation using MT
				if (j == 0) { // if we are in the first time stamp
					s = s * std::exp(const_exposant * timesteps[0] + volatility * sqrt(timesteps[0]) * Z);
					// we use the first formula
				}
				else { // else we use the other one
					s = s * std::exp(const_exposant * (timesteps[j]- timesteps[j-1]) + volatility * sqrt(timesteps[j] - timesteps[j - 1]) * Z);
				}

				S_vect.push_back(s); // we had the value into the vector that stors theme
			}

			double payoff = asian_option->payoffPath(S_vect); // at the end, we calculate the payoff with the path
			sum_payoff = sum_payoff + payoff; // adding payoff
			sum_payoff_carre = sum_payoff_carre + pow(payoff, 2); // adding payoff square
			
		}
		else {
			// if the option is european or american m=1
			double Z = MT::rand_norm(); // random generation using MT
			s = s * std::exp(const_exposant * expiry + volatility * sqrt(expiry) * Z); // we use the formula given in the project

			double payoff = option->payoff(s); // get the payoff
			sum_payoff += payoff; // adding it to the sum payoff variable
			sum_payoff_carre += pow(payoff, 2);
		}

	}

	curent_estimate_price = std::exp((-initerest_rate * expiry)) * (1.0 / nb_generate) * sum_payoff;
	// calculate the current estimate
	
}

double BlackScholesMCPricer::operator() () {
	if (nb_generate == 0) { // if we don't have any value generated, so we don't have price
		throw std::runtime_error("aucune simulation n a été effectuée"); // we have an error
	}
	return curent_estimate_price; // else we return the price
}

std::vector<double> BlackScholesMCPricer::confidenceInterval() { // at 95% here

	std::vector<double> intervalle_confiance; // initialize the vector of the IC [... , ...]

	if (nb_generate == 0) { // if we don't have any value generated, so we don't have price
		throw std::runtime_error("aucune simulation n a été effectuée");
	}
	else {
		double mean = sum_payoff / nb_generate; // then, we calculate the mean
		double variance = (sum_payoff_carre / nb_generate) - pow(mean, 2);
		// we use here the biase estimator of variance because without biase we need to calculate the sum at each increments
		// it's not very efficient
		double ecart_type = sqrt(variance); // standard deviation
		double marge = 1.96 * ecart_type / sqrt(nb_generate); // we get the margin that will be use to do + or - the price into
		// the confidence interval
		intervalle_confiance.push_back(curent_estimate_price - marge); // creating the IC
		intervalle_confiance.push_back(curent_estimate_price + marge);
	}
	
	return intervalle_confiance;

}