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

}