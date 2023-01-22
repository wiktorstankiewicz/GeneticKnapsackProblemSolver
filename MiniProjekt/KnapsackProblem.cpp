#include "KnapsackProblem.h"

double KnapsackProblem::fitness(Pointer<Individual>& ind)
{
	if (statusCode != KNAPSACK_PROBLEM_STATUS_OK) {
		std::cout << "Tried using invalidly instantiated object\n";
		return -1;
	}


	if (ind == nullptr) {
		return 0;
	}

	double totalValue = 0;
	double totalWeight = 0;
	std::vector<bool> genotype = ind->getGenotype();
	for (int i = 0; i < valueWeightPairs.size(); i++) {
		if (genotype[i] == true) {
			totalWeight += valueWeightPairs[i].second;
			totalValue += valueWeightPairs[i].first;
		}
	}
	if (totalWeight > maxWeight) {
		return 0.0;
	}
	return totalValue;
}

KnapsackProblem::KnapsackProblem(const double _maxWeight, std::vector<std::pair<double, double>> _valueWeightPairs)
{
	maxWeight = _maxWeight;
	valueWeightPairs = _valueWeightPairs;

	if (maxWeight <= 0) {
		statusCode = KNAPSACK_PROBLEM_STATUS_INVALID_ARGUMENTS;
		return;
	}
	bool valueWeightPairsContainInvalidData = false;
	for (int i = 0; i < valueWeightPairs.size(); i++) {
		if (valueWeightPairs[i].first < 0 || valueWeightPairs[i].second <= 0) {
			statusCode = KNAPSACK_PROBLEM_STATUS_INVALID_ARGUMENTS;
			return;
		}
	}
	statusCode = KNAPSACK_PROBLEM_STATUS_OK;
}

KnapsackProblem::KnapsackProblem()
{
	maxWeight = -1;
	statusCode = KNAPSACK_PROBLEM_STATUS_NOT_INITIALIZED;
};