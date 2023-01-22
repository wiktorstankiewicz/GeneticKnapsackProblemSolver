#pragma once
#include <vector>
#include "Pointer.h"
#include "Individual.h"
#include "KnapsackProblem.h"
#include "MyRandomLib.h"
#include <Windows.h>

#define STATUS_PROPERLY_INITIALIZED 0
#define STATUS_BAD_INITIALIZATION 1
#define STATUS_FINISHED 2
class GeneticAlgorithm
{
public:
	GeneticAlgorithm(int popSize, double mutProb, double crossProb, int numberOfIterations, KnapsackProblem& knapsackProblem);
	void run(bool debug);
	void getBestSolution();
	void printAllNonZeroIndividuals();
	int getStatusCode();
private:
	int statusCode;
	int popSize;
	int numberOfIterations;
	double mutProb;
	double crossProb;

	KnapsackProblem knapsackProblem;
	Pointer<Individual> bestIndividual;
	vector<Pointer<Individual>> populationPool;


	std::vector<bool> randomizeGenotype(int amountOfGenes);
	double averageFitness();
	void select2RandomIndividuals(Pointer<Individual>& individual1, Pointer<Individual>& individual2);
	void performSimulationStep();
	void selectParents(Pointer<Individual>& parent1, Pointer<Individual>& parent2);
	void initializePopulationPool();
	void searchForNewBest();
};

