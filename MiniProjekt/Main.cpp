#include<iostream>
#include"GeneticAlgorithm.h"
#include "KnapsackProblem.h"
#include"KnapsackProblemUtils.h"


int popSize = 300;
double mutProb = 0.1;
double crossProb = 0.8;
int iterations = 500;
string path = "3.txt";
int debugMode = false;

int main()
{
	KnapsackProblem knapsackProblem;
	KnapsackProblemUtils::load(path, knapsackProblem);

	if (knapsackProblem.getStatusCode() != KNAPSACK_PROBLEM_STATUS_OK) {
		std::cout << "ERROR: KnapsackProblem object was initialized with bad arguments or was not yet initialized\n";
		return 0;
	}


	GeneticAlgorithm genAlg(popSize, mutProb, crossProb, iterations, knapsackProblem);
	if (genAlg.getStatusCode() == STATUS_PROPERLY_INITIALIZED) {
		genAlg.run(debugMode);
	}
	if(genAlg.getStatusCode() == STATUS_BAD_INITIALIZATION) {
		std::cout << "ERROR: GeneticAlgorithm object was initialized with bad arguments\n";
		return 0;
	}



	if (genAlg.getStatusCode() == STATUS_FINISHED) {
		genAlg.getBestSolution();
	}
	else {
		std::cout << "ERROR: An error has occured\n";
	}

	std::cout << "Actual best solution: " << KnapsackProblemUtils::findActualBestSolutionFitness(path);
	return 0;
}
