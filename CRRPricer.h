#pragma once
#include "Option.h"
#include "BinaryTree.h"
#include <iostream>

class CRRPricer
{
private:	
	Option* option;
	int depth;
	double asset_price;
	double up;
	double down;
	double interest_rate;
	BinaryTree<double> tree;
	

	double S(int, int);



public:
	CRRPricer(Option*, int, double, double, double, double);
	void Compute();
	double get(int, int);
	void set(int, int, double);
	double operator()(bool=false);
	double factorial(double);

};

