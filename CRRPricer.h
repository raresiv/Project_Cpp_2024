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
	double S(int,int);
	BinaryTree<double> tree;


public:
	CRRPricer(Option*, int, double, double, double, double, BinaryTree<double>);
	BinaryTree<double> tree_structure();
	void Compute();
	double get(int, int);
	double operator()(bool);
	int factorial(int);

};

