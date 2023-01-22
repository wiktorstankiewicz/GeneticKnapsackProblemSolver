#include "Individual.h"


Individual::Individual(std::vector<bool> _genotype)
{
	genotype = _genotype;
}


void Individual::mutate(const double mutProb)
{
	for (int i = 0; i < genotype.size(); i++) {
		if (MyRandomLib::randomDoubleInclusive(0, 1) < mutProb) {
			genotype[i] = !genotype[i];
		}
	}
}

void Individual::cross(Pointer<Individual>& _otherParent, Pointer<Individual>& firstChild, Pointer<Individual>& secondChild)
{
	Individual otherParent = *_otherParent;

	int firstPosition = 1;
	int lastPosition = otherParent.genotype.size() - 2;

	int divisionIndex = MyRandomLib::randomIntInclusive(1, otherParent.genotype.size() - 1);
	std::vector<bool> child1Genotype = vector<bool>(genotype.size());
	std::vector<bool> child2Genotype = vector<bool>(genotype.size());


	for (int i = 0; i < divisionIndex; i++) {
		child1Genotype[i] = genotype[i];
		child2Genotype[i] = otherParent.genotype[i];
	}
	for (int i = divisionIndex; i < genotype.size(); i++) {
		child1Genotype[i] = otherParent.genotype[i];
		child2Genotype[i] = genotype[i];
	}

	firstChild = Pointer<Individual>(new Individual(child1Genotype));
	secondChild = Pointer<Individual>(new Individual(child2Genotype));
	
}

void Individual::printGenotype()
{
	std::cout << "[";
	for (int i = 0; i < genotype.size() -1; i++) {
		std::cout << genotype[i] << " ";
	}
	std::cout << genotype[genotype.size() -1];
	std::cout << "]";
}

std::vector<bool> Individual::getGenotype()
{
	return genotype;
}
