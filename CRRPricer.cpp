	#include "CRRPricer.h"


CRRPricer::CRRPricer(Option* opt, int N, double S, double U, double D, double R, BinaryTree<double> arbre) :
	option(opt),depth(N),asset_price(S),up(U),down(D),interest_rate(R),tree(arbre) 
{
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

void CRRPricer::Compute(){	

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



double CRRPricer::operator()(bool closed_form = false)
{
	double H = 0;
	double h;
	double a;
	double b;
	double q = (interest_rate - down) / (up - down);
	if (closed_form)
	{
		for (int i = 0; i < depth; i++)
		{
			h = option->payoff(S(depth, i));
			a = factorial(depth) / (factorial(i) * factorial(depth - i));
			b = pow(q, i) * pow(1 - q, depth - i);
			H = H + h * a * b;
		}
		H = H / (pow(1 + interest_rate, depth));
	}

//il faut utiliser le compute ici mais pas bien compris 

	return H;
}

int CRRPricer::factorial(int n)
{
	if (n == 0) return 1;
	return n * factorial(n - 1);
}

double CRRPricer::get(int n, int i) {	//Version Alternative
	int compteur = 0;
	double q = (interest_rate - down) / (up - down);
	double result = option->payoff(asset_price * pow(1 + up, i + 1) * pow(1 + down, depth - i - 1));	//Prix à maturité au noeud i
	if (compteur == depth - i)
		return result;
	else {
		compteur += 1;	//Compteur augmenté de 1 pour atteindre la limite du dessus (total - i)
		return (q * get(n + 1, i + 1) + (1 - q) * get(n + 1, i))/(1+interest_rate);	
		//Formule utilisé car payoff dans la formule est utilisée juste pour maturité pas pour le reste (le reste on utilise les deux prix d'avant)
	}
	
}


