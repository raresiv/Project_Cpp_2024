#include "BlackScholesMCPricer.h"


BlackScholesMCPricer::BlackScholesMCPricer(Option* opt, double ip, double ir, double vol){
	option = opt;
	initial_price = ip;
	initerest_rate = ir;
	volatility = vol;
	nb_paths = 0;
};

int BlackScholesMCPricer::getNbPaths() {
	return nb_paths;
}

void BlackScholesMCPricer::generate(int nb_paths) {
	double expiry = option->getExpiry();
	double const_exposant = initerest_rate - (pow(volatility,2) / 2);
	double s0 = initial_price;
	double sum_payoffs = 0.0;
	for (int i = 0; i < nb_paths; i++) {

		// Sdouble Z = MT::rand_norm();

	}
}