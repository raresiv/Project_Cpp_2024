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
	sum_payoff = 0;
	curent_estimate_price = 0;
};

int BlackScholesMCPricer::getNbPaths() {
	return nb_generate;
}

void BlackScholesMCPricer::generate(int nb_paths) {
	double expiry = option->getExpiry();
	double const_exposant = initerest_rate - (pow(volatility,2) / 2);
	double s = initial_price;
	nb_generate = nb_generate + nb_paths;
	for (int i = 0; i < nb_paths; i++) {
		
		if (option->isAsianOption() == true) {
			double Z = MT::rand_norm(); // random generation using MT
			AsianOption* asian_option = dynamic_cast<AsianOption*>(option);
			std::vector<double> timesteps = asian_option->getTimeSteps();
			std::vector<double> S_vect;
			for (int i = 0; i < timesteps.size(); i++) {
				if (i == 0) {
					s = s * std::exp(const_exposant * timesteps[0] + volatility * pow(timesteps[0], 1 / 2) * Z);
				}
				else {
					s = s * std::exp(const_exposant * (timesteps[i]- timesteps[i-1]) + volatility * pow(timesteps[i] - timesteps[i - 1], 1 / 2) * Z);
				}

				S_vect.push_back(s);
			}

			double payoff = asian_option->payoffPath(S_vect);
			sum_payoff = sum_payoff + payoff;
			sum_payoff_carre = sum_payoff_carre + pow(payoff, 2);
			
		}
		else {

			// si l option est Européenne m=1
			double Z = MT::rand_norm();
			s = s * std::exp(const_exposant * expiry + volatility * pow(expiry, 1 / 2) * Z);
			sum_payoff = s;
		}

	}

	curent_estimate_price = std::exp((-initerest_rate * expiry)) * (1. / nb_generate) * sum_payoff;
	
}

double BlackScholesMCPricer::operator() () {
	if (nb_generate == 0) {
		throw std::runtime_error("aucune simulation n a été effectuée");
	}
	return curent_estimate_price;
}

std::vector<double> BlackScholesMCPricer::confidenceInterval() { // at 95%

	std::vector<double> intervalle_confiance;

	if (nb_generate == 0) {
		throw std::runtime_error("aucune simulation n a été effectuée");
	}
	else {
		double moyenne = sum_payoff / nb_generate;
		double variance = (sum_payoff_carre / nb_generate) - pow(moyenne, 2); // on utilise l'estimateur biaisé de la variance 
		// car pour calculer celui sans biais il faudrait faire des sommes a chaque increment (pas faisable)
		double ecart_type = pow(variance, 1/2);
		double marge = 1.96 * ecart_type * (1 / pow(nb_generate, 1 / 2));
		intervalle_confiance.push_back(curent_estimate_price - marge);
		intervalle_confiance.push_back(curent_estimate_price + marge);
	}
	
	return intervalle_confiance;

}