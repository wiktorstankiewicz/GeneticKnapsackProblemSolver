#pragma once
#include<vector>
#include"Individual.h"


#define KNAPSACK_PROBLEM_STATUS_NOT_INITIALIZED -1
#define KNAPSACK_PROBLEM_STATUS_OK 0
#define KNAPSACK_PROBLEM_STATUS_INVALID_ARGUMENTS 1


class KnapsackProblem
{
public:
	double fitness(Pointer<Individual>& ind);
	KnapsackProblem(const double maxWeight, std::vector<std::pair<double, double>> valueWeightPairs);
	KnapsackProblem();
	int getStatusCode() { return statusCode; };
	int getAmountOfItems() { return valueWeightPairs.size(); };
private:
	double maxWeight;
	std::vector<std::pair<double, double>> valueWeightPairs;
	int statusCode;
};


