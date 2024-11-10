	#include "CRRPricer.h"


CRRPricer::CRRPricer(Option* opt, int N, double S, double U, double D, double R) {
	option = opt;
	depth = N;
	asset_price = S;
	up = U;
	down = D;
	interest_rate = R;

	if (D < R < U) {
		std::cout << " NO ARBITRAGE";
	}
	else {
		std::cout << "BE CAREFUL ARBITRAGE";
	}
}

double CRRPricer::S(int n,int i)
{
	return asset_price* pow((1 + up), i)* pow(1 + down, n - i);
}

BinaryTree<double> CRRPricer::tree_structure() {
	BinaryTree<double> tree(depth);
	tree.setNode(0, 0, asset_price);
	return tree;

}

void CRRPricer::Compute(){
	BinaryTree<double> tree = tree_structure();
	for (int i = 0; i < depth; i++) {
		for (int j = 0; j < depth; j++) {
			double current_price = S(depth,i);
			double current_payoff = option->payoff(current_price);
			tree.setNode(i, j, current_payoff);
		}
	}
}

double CRRPricer::get(int n, int i) {

	double current_payoff = option->payoff(S(depth,i));
	double temp1 = option->payoff(S(depth-1,i+1));//asset_price * pow((1 + up), i+1) * pow(1 + down, depth - i -1)
	double temp2 = current_payoff;
	double result;
	double q = (interest_rate - down) / (up - down);
	for (int j = depth - 1; j >= n; j--) {
		result = (q * temp1 + (1 - q) * temp2) / (1 + interest_rate);
		temp1 = option->payoff(S(j-1,i+1)); //asset_price* pow((1 + up), i + 1)* pow(1 + down, j - i - 1)
		temp2 = option->payoff(S(j,i));//asset_price * pow((1 + up), i) * pow(1 + down, j - i)
	}


	return result;
	
	
}

