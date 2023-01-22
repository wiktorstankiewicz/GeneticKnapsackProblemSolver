#pragma once
#include<vector>
#include"Pointer.h"
#include "MyRandomLib.h"
#include <bitset>

using namespace std;
class Individual {
public:
	Individual(std::vector<bool> genotype);
	void mutate(const double mutProb);
	void cross(Pointer<Individual>& parent, Pointer<Individual>& firstChild, Pointer<Individual>& secondChild);
	void printGenotype();
	bool operator==(const Individual& other) { return this == &other; };
	bool operator!=(const Individual& other) { return !(this == &other); };
	std::vector<bool> getGenotype();
private:
	std::vector<bool> genotype;
};
