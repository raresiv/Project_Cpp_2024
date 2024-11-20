	#include "CRRPricer.h"


// Constructeur avec valeur par défaut pour arbre
CRRPricer::CRRPricer(Option* opt, int N, double S, double U, double D, double R)
	: option(opt), depth(N), asset_price(S), up(U), down(D), interest_rate(R) {

	tree = BinaryTree<double>(N);

	if (D < R && R < U) {
		std::cout << "NO ARBITRAGE";
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


	//Initialisation du prix avec les payoffs à maturité
	for (int j = 0; j <= depth; j++) {
		double payoff = option->payoff(S(j, depth));	//Payoff à maturité au noeud i qui vaut j
		tree.setNode(j, depth, payoff);	//On remplit l'arbre à maturité
	}

	double q = (interest_rate - down) / (up - down);

	//Double Boucle remplissage arbre
	for (int n = depth-1; n >= 0; n--) {
		for (int i = 0; i <= n; i++)	//les i vont de 0 à n spour chaque profondeur
		{
			
			double price = (q * tree.getNode(i + 1, n) + (1 - q) * tree.getNode(i, n))/(1+interest_rate);	//Calcul du prix avec la profondeur supérieur
			tree.setNode(i, n, price);	//On remplit la profondeur n pour chaque i
		}
	}
		
			
}

double CRRPricer::get(int n, int i) {
	return tree.getNode(n, i);

}


//double CRRPricer::get(int n, int i) {
//
//	double current_payoff = option->payoff(S(depth,i));
//	double temp1 = option->payoff(S(depth-1,i+1));//asset_price * pow((1 + up), i+1) * pow(1 + down, depth - i -1)
//	double temp2 = current_payoff;
//	double result;
//	double q = (interest_rate - down) / (up - down);
//	for (int j = depth - 1; j >= n; j--) {
//		temp1 = (q * result + (1 - q) * temp2) / (1 + interest_rate);
//		temp2 = (q * temp1 + (1 - q) * temp2) / (1 + interest_rate);
//		result = (q * temp1 + (1 - q) * temp2) / (1 + interest_rate);
//	}
//
//
//	return result;
//	
//	
//}

double CRRPricer::factorial(double n)
{
	if (n <= 0) {
		return 1;
	}
	else {
		return n * factorial(n - 1);
	}

}

double CRRPricer::operator()(bool closed_form)
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



//double CRRPricer::get(int n, int i) {	//Version Alternative
//	int compteur = 0;
//	double q = (interest_rate - down) / (up - down);
//	double result = option->payoff(asset_price * pow(1 + up, i + 1) * pow(1 + down, depth - i - 1));	//Prix à maturité au noeud i
//	if (compteur == depth - i)
//		return result;
//	else {
//		compteur += 1;	//Compteur augmenté de 1 pour atteindre la limite du dessus (total - i)
//		return (q * get(n + 1, i + 1) + (1 - q) * get(n + 1, i))/(1+interest_rate);	
//		//Formule utilisé car payoff dans la formule est utilisée juste pour maturité pas pour le reste (le reste on utilise les deux prix d'avant)
//	}
//	
//}


