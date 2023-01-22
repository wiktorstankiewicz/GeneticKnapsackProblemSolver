#pragma once
#include"KnapsackProblem.h"
#include<fstream>
#include<sstream>
#include<string>

#define STATUS_BAD 0
#define STATUS_OK 1
#define MAX_NUMBER_LENGTH 256
namespace KnapsackProblemUtils
{
	void load(string& path, KnapsackProblem& knapsackProblem);
	double findActualBestSolutionFitness(const string& path);
};

