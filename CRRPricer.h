#pragma once
#include "Option.h"
#include "AmericanCallOption.h"
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
	BinaryTree<bool> exercise_tree;

	double S(int, int);



public:
	CRRPricer(Option*, int, double, double, double, double);
	CRRPricer(Option*, int, double, double, double);
	bool getExercise(int, int);
	void compute();
	double get(int, int);
	void set(int, int, double);
	double operator()(bool=false);
	double factorial(double);

};

