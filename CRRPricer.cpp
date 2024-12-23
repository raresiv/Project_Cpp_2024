	#include "CRRPricer.h"



// Constructor with the fixed value of up and down and without the value of the volatility

CRRPricer::CRRPricer(Option* opt, int N, double S, double U, double D, double R)
	: option(opt), depth(N), asset_price(S), up(U), down(D), interest_rate(R)  {

	//Initilialize the trees
	tree = BinaryTree<double>(N);				//Tree for the value of the option at the node n,i
	exercise_tree = BinaryTree<bool>(N);		//Tree for the american option wheter or not we exercice it at the node n,i

	//Define whether or not there is Arbitrage
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

//Constructor with the up and down variables dependent of the variables R sigma the deepth of the tree and the maturity of the option (expiry)

CRRPricer::CRRPricer(Option* opt, int N, double S, double R, double sigma)
    : option(opt), depth(N), asset_price(S), interest_rate(R) {

    // Calculate the timestep with mautirty and the deepth of the tree
    double timestep = option->getExpiry() / N;

    // Formulas for values of up down and interest rate
    up = exp((R + (sigma * sigma) / 2) * timestep + sigma * sqrt(timestep)) - 1;
    down = exp((R + (sigma * sigma) / 2) * timestep - sigma * sqrt(timestep)) - 1;
    interest_rate = exp(R * timestep) - 1;
	
    // Initialze the trees like above
    tree = BinaryTree<double>(N);
    exercise_tree = BinaryTree<bool>(N);

    // Arbitrage check
    if (down < interest_rate && interest_rate < up){
        std::cout << "NO ARBITRAGE" << std::endl;
    } else {
        std::cout << "BE CAREFUL ARBITRAGE" << std::endl;
    }

    if (opt->isAsianOption() == true) {
        throw std::runtime_error("Asian options are not supported in CRRPricer.");
    }
}


//Function for calculating the price of the asset at the node (n, i) depending of which constructor we used


double CRRPricer::S(int n,int i)
{
	return asset_price* pow((1 + up), i)* pow(1 + down, n - i);
}


//Function to fill the tree of values of the option 

void CRRPricer::compute(){	


	/*
	We start from the end of the tree(at maturity).
	We fill each value of the tree at the depth with its payoff from the price of the asset at the node (depth, i) ,
	with i that determines how many times the asset went up during after all the timestep
	*/

	for (int j = 0; j <= depth; j++) {
		double payoff = option->payoff(S(depth, j));	//We call the payoff of the option with the price of the asset at maturity that went j times up
		tree.setNode(depth , j, payoff);				//We fill the tree of the value of the option with value above

		//For the American Option we initialize the exercise tree if the payoff is positive at maturity we exercise the option but if not we don't exercise it
		if (option->isAmericanOption()) {
			if (payoff > 0) {
				exercise_tree.setNode(depth, j, true);
			}
			else {
				exercise_tree.setNode(depth, j, false);
			}
			
		}
			
	}



	double q = (interest_rate - down) / (up - down);
	
	/*
	After initialize the tree at the deepest level we now fill both trees for the rest of all the nodes
	We are going to vacate in the trees from the deepest level to the the summit.
	To do that we are going to have a first loop for the timestep and for another loop because for each timestep we have the amount the deepest level-the level we already vacate to.
	*/
	for (int n = depth; n >= 0; n--) {	// We first vacate with n through all the timestep starting from the end
		for (int i = 0; i <= n; i++)	// We then vacate for each timestep n throught all the possible values of the option at the timestep n with i 
		{
			
			//We split the case of the american option and the rest because of the power of the maerican option to be exercise at any timestep and we have to fill also the exercise tree !
			if (option->isAmericanOption()){
				
				//We calcultate at every nodes the value of the option and the payoff to see if it is interesting or not to exercise it
				double continuation_value = (q * tree.getNode(n, i + 1) + (1 - q) * tree.getNode(n, i))/(1+interest_rate);	
				double intrinsic_value = option->payoff(S(n-1,i));


				double price = std::max(continuation_value, intrinsic_value);
				tree.setNode(n-1, i, price);	//We take the maximum between the value and the payoff of the option to fill the tree of the value of the option
				
				//If the value is greater than the payoff we exercise the option ! So we set to true the value at the node (n,i) in the exercise tree
				bool exercise = intrinsic_value >= continuation_value;
            	exercise_tree.setNode(n, i, exercise);
			}
			// BUT if it's not an american option we just put for every nodes the value of the option with the formula given in the project
			else{

				double price = (q * tree.getNode(n, i + 1) + (1 - q) * tree.getNode(n, i))/(1+interest_rate);	
				tree.setNode(n-1, i, price);	
			}
			

		}
	}
		
			
}

//Getter function to have the bool of the node (i,n) whether or not we exercise the option
bool CRRPricer::getExercise(int i, int n){
	return exercise_tree.getNode(i,n);
}

//Same thing for the tree of the value of the option but this time it's double variable
double CRRPricer::get(int n, int i) {
	return tree.getNode(n, i);

}

//Factorial function to make calculations easier
double CRRPricer::factorial(double n)
{
	if (n <= 0) {
		return 1;
	}
	else {
		return n * factorial(n - 1);
	}

}

/*
Function that return the value of the option with a bool in parameters initialized to false in the.h
If this bool is true it will return the value from CRR method given in the project
Else this bool will return the value from the tree in the function compute
*/
double CRRPricer::operator()(bool closed_form)
{
	double H = 0;
	double h;
	double a;
	double b;
	double q = (interest_rate - down) / (up - down);
	//Case of the bool closed_form being true and the function will return H that takes the value from the CRR method
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
	//Case of the bool closed_form being false so the function will run the function compute and fill the tree or trees and take the value at the summit of the tree
	else {
		compute();
		H = tree.getNode(0, 0);
	}


	return H;
}





