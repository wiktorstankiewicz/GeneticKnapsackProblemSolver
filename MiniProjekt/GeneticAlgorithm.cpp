#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(const int _popSize, const double _mutProb, const double _crossProb, const int _numberOfIterations, KnapsackProblem& _knapsackProblem)
{
	popSize = _popSize;
	mutProb = _mutProb;
	crossProb = _crossProb;
	numberOfIterations = _numberOfIterations;
	knapsackProblem = _knapsackProblem;

	if (popSize <= 0 || (mutProb < 0 || mutProb > 1) || (crossProb < 0 || crossProb > 1) || numberOfIterations <= 0 || popSize%2 != 0) {
		statusCode = STATUS_BAD_INITIALIZATION;
	}
	else {
		statusCode = STATUS_PROPERLY_INITIALIZED;
	}
}

void GeneticAlgorithm::run(bool debug)
{
	if (statusCode == STATUS_BAD_INITIALIZATION) {
		std::cout << "Error: Object was not properly initialized\n";
		return;
	}
	if (statusCode == STATUS_FINISHED) {
		std::cout << "Error: Algorithm was already used. Use getBestSolution() to display the result.\n";
		return;
	}

	if (debug) {
		std::cout << "Initializing population\n";
		Sleep(1000);
	}
	initializePopulationPool();
	searchForNewBest();
	int i = 0;
	while (i < numberOfIterations) {
		std::cout << "Population " << i + 1 << " Avg fitness: " << averageFitness() << "\n";
		if (debug) {
			printAllNonZeroIndividuals();
		}
		performSimulationStep();
		searchForNewBest();
		i++;
	}
	
	statusCode = STATUS_FINISHED;

}


void GeneticAlgorithm::getBestSolution()
{
	if (statusCode == STATUS_BAD_INITIALIZATION) {
		std::cout << "Error: Object was not properly initialized\n";
		return;
	}

	if (statusCode == STATUS_PROPERLY_INITIALIZED) {
		std::cout << "Error: run() method wasn't yet called. Call run() method before asking for solution";
		return;
	}

	if (bestIndividual == nullptr) {
		std::cout << "Solution not found!\n";
		return;
	}
	std::cout << "Best solution found: ";
	bestIndividual->printGenotype();
	std::cout << "\nFitness: " << knapsackProblem.fitness(bestIndividual) << "\n";
}

void GeneticAlgorithm::printAllNonZeroIndividuals()
{
	std::cout << "Non-zero fitness individuals:\n";
	for (int i = 0; i < populationPool.size(); i++) {
		if (knapsackProblem.fitness(populationPool[i]) > 0) {
			std::cout << i << ": ";
			populationPool[i]->printGenotype();
			std::cout << "f: " << knapsackProblem.fitness(populationPool[i]) << "\n";

		}
	}
	std::cout << "\n";
}

int GeneticAlgorithm::getStatusCode()
{
	return statusCode;
}


void GeneticAlgorithm::performSimulationStep()
{
	std::vector<Pointer<Individual>> newPool;
	Pointer<Individual> parent1(nullptr), parent2(nullptr), child1(nullptr), child2(nullptr);
	while (newPool.size() < popSize) {
		selectParents(parent1, parent2);
		if (MyRandomLib::randomDoubleInclusive(0, 1) < crossProb) {
			parent1->cross(parent2, child1, child2);
			child1->mutate(mutProb);
			child2->mutate(mutProb);
			newPool.push_back(child1);
			newPool.push_back(child2);
		}
		else {
			newPool.push_back(parent1);
			newPool.push_back(parent2);
		}
	}
	populationPool = newPool;
}

void GeneticAlgorithm::selectParents(Pointer<Individual>& parent1, Pointer<Individual>& parent2)
{
	if (popSize == 2) {
		parent1 = populationPool[0];
		parent2 = populationPool[1];
		return;
	}

	Pointer<Individual> candidate1(nullptr), candidate2(nullptr);
	select2RandomIndividuals(candidate1, candidate2);
	if (knapsackProblem.fitness(candidate1) > knapsackProblem.fitness(candidate2)) {
		parent1 = candidate1;
		parent2 = candidate1;
	}
	else {
		parent1 = candidate2;
		parent2 = candidate2;
	}
	while (*parent1 == *parent2) {
		select2RandomIndividuals(candidate1, candidate2);
		if (knapsackProblem.fitness(candidate1) > knapsackProblem.fitness(candidate2)) {
			parent2 = candidate1;
		}
		else {
			parent2 = candidate2;
		}
	}
}

void GeneticAlgorithm::initializePopulationPool()
{
	Pointer<Individual> randomIndividual(nullptr);
	for (int i = 0; i < popSize; i++) {
		std::vector<bool> genotype = randomizeGenotype(knapsackProblem.getAmountOfItems());
		randomIndividual = Pointer<Individual>(new Individual(genotype));
		populationPool.push_back(randomIndividual);
	}
}

std::vector<bool> GeneticAlgorithm::randomizeGenotype(int amountOfGenes)
{
	std::vector<bool> genotype = std::vector<bool>(amountOfGenes);
	for (int i = 0; i < amountOfGenes; i++) {
		genotype[i] = MyRandomLib::randomIntInclusive(0, 1);
	}

	return genotype;
}

void GeneticAlgorithm::select2RandomIndividuals(Pointer<Individual>& individual1, Pointer<Individual>& individual2)
{
	int index1 = 0, index2 = 0;

	while (index1 == index2) {
		index1 = MyRandomLib::randomIntInclusive(0, populationPool.size() - 1);
		index2 = MyRandomLib::randomIntInclusive(0, populationPool.size() - 1);
	}
	individual1 = populationPool[index1];
	individual2 = populationPool[index2];

}

void GeneticAlgorithm::searchForNewBest()
{
	for (int i = 0; i < populationPool.size(); i++) {
		if (knapsackProblem.fitness(populationPool[i]) > knapsackProblem.fitness(bestIndividual)) {
			bestIndividual = populationPool[i];
		}
	}
}

double GeneticAlgorithm::averageFitness()
{
	double sum = 0;
	int i = 0;
	for (i = 0; i < populationPool.size(); i++) {
		sum += knapsackProblem.fitness(populationPool[i]);
	}
	return sum / (i);

}


