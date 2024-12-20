	#include "CRRPricer.h"



// Constructeur avec valeur par défaut pour arbre
CRRPricer::CRRPricer(Option* opt, int N, double S, double U, double D, double R)
	: option(opt), depth(N), asset_price(S), up(U), down(D), interest_rate(R)  {

	tree = BinaryTree<double>(N);
	exercise_tree = BinaryTree<bool>(N);

	if (D < R && R < U) {
		std::cout << "NO ARBITRAGE";
		std::cout << std::endl;

	}
	else {
		std::cout << "BE CAREFUL ARBITRAGE";
		std::cout << std::endl;
	}
	if (opt->isAsianOption() == true) {
		throw std::runtime_error("Asian options are not supported in CRRPricer.");
	}
}

CRRPricer::CRRPricer(Option* opt, int N, double S, double R, double sigma)
    : option(opt), depth(N), asset_price(S), interest_rate(R) {

    // Calcul de la taille d'un pas de temps
    double timestep = option->getExpiry() / N;

    // Initialisation des paramètres U, D et R
    up = exp((R + (sigma * sigma) / 2) * timestep + sigma * sqrt(timestep)) - 1;
    down = exp((R + (sigma * sigma) / 2) * timestep - sigma * sqrt(timestep)) - 1;
    interest_rate = exp(R * timestep) - 1;
	

    // Initialisation des arbres
    tree = BinaryTree<double>(N);
    exercise_tree = BinaryTree<bool>(N);

    // Vérification de l'absence d'arbitrage
    if (down < interest_rate && interest_rate < up) {
        std::cout << "NO ARBITRAGE" << std::endl;
    } else {
        std::cout << "BE CAREFUL ARBITRAGE" << std::endl;
    }

    // Vérification que l'option n'est pas asiatique
    if (opt->isAsianOption() == true) {
        throw std::runtime_error("Asian options are not supported in CRRPricer.");
    }
}

double CRRPricer::S(int n,int i)
{
	return asset_price* pow((1 + up), i)* pow(1 + down, n - i);
}





void CRRPricer::compute(){	


	//Initialisation du prix avec les payoffs à maturité
	for (int j = 0; j <= depth; j++) {
		double payoff = option->payoff(S(depth, j));	//Payoff à maturité au noeud i qui vaut j
		tree.setNode(depth , j, payoff);	//On remplit l'arbre à maturité
		exercise_tree.setNode(depth, j, true);		//On remplit l'arbre de booléens à maturité en true
	}

	double q = (interest_rate - down) / (up - down);
	//Double Boucle remplissage arbre
	for (int n = depth; n >= 0; n--) {
		for (int i = 0; i <= n; i++)	//les i vont de 0 à n pour chaque profondeur
		{
			
			
			if (option->isAmericanOption()){
				double continuation_value = (q * tree.getNode(n, i + 1) + (1 - q) * tree.getNode(n, i))/(1+interest_rate);	//Calcul du prix avec la profondeur supérieur
				double intrinsic_value = option->payoff(S(n-1,i));


				double price = std::max(continuation_value, intrinsic_value);
				tree.setNode(n-1, i, price);	//On remplit la profondeur n pour chaque i
			
				bool exercise = intrinsic_value >= continuation_value;
            	exercise_tree.setNode(n, i, exercise);
			} 
			else{
				double price = (q * tree.getNode(n, i + 1) + (1 - q) * tree.getNode(n, i))/(1+interest_rate);	//Calcul du prix avec la profondeur supérieur
				tree.setNode(n-1, i, price);	//On remplit la profondeur n pour chaque i
			}
			

		}
	}
		
			
}

bool CRRPricer::getExercise(int i, int n){
	return exercise_tree.getNode(i,n);
}

double CRRPricer::get(int n, int i) {
	return tree.getNode(n, i);

}

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
	else {
		compute();
		H = tree.getNode(0, 0);
	}


	return H;
}





