#include "KnapsackProblemUtils.h"

namespace {

	double knapSackRec(int W, std::vector<std::pair<double, double>> valueWeightPairs, int i, double** dp)
	{
		if (i < 0)
			return 0;
		if (dp[i][W] != -1)
			return dp[i][W];

		if (valueWeightPairs[i].second > W) {

			dp[i][W] = knapSackRec(W, valueWeightPairs, i - 1, dp);
			return dp[i][W];
		}
		else {
			dp[i][W] = max(valueWeightPairs[i].first
				+ knapSackRec(W - valueWeightPairs[i].second, valueWeightPairs,
					i - 1, dp),
				knapSackRec(W, valueWeightPairs, i - 1, dp));

			return dp[i][W];
		}
	}

	double knapSack(int W, std::vector<std::pair<double, double>> valueWeightPairs, int n)
	{
		double** dp;
		dp = new double* [n];

		for (int i = 0; i < n; i++)
			dp[i] = new double[W + 1];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < W + 1; j++)
				dp[i][j] = -1;
		return knapSackRec(W, valueWeightPairs, n - 1, dp);
	}


	int loadInstanceFromFile(const string& path, double& maxCapacity, std::vector<std::pair<double, double>>& weightValuePairs)
	{
		char buffer[MAX_NUMBER_LENGTH];
		double weightBuffer = 0;
		double valueBuffer = 0;
		ifstream file(path);


		if (file.fail() || file.bad()) {
			std::cout << "ERROR Could not access file " << path << "\n";
			return STATUS_BAD;
		}

		int lineNumber = 1;
		if (!file.eof()) {
			file.istream::get(buffer, MAX_NUMBER_LENGTH, '\n');
			file.istream::get();
			try {
				maxCapacity = std::stod(buffer);

			}
			catch (invalid_argument) {
				std::cout << "ERROR Line " << lineNumber << " expected one double value\n";
				return STATUS_BAD;
			}
		}

		lineNumber++;
		while (!file.eof()) {
			file.istream::get(buffer, MAX_NUMBER_LENGTH, ' ');
			try {
				valueBuffer = std::stod(buffer);
			}
			catch (invalid_argument) {
				std::cout << "ERROR Line: " << lineNumber << " Expected 2 double values separated by a space\n";
				return STATUS_BAD;
			}
			if (valueBuffer < 0) {
				std::cout << "ERROR Line: " << lineNumber << " Expected non-negative values\n";
				return STATUS_BAD;
			}



			file.istream::get();

			file.istream::get(buffer, MAX_NUMBER_LENGTH, '\n');
			try {
				weightBuffer = std::stod(buffer);
			}
			catch (invalid_argument) {
				std::cout << "ERROR Line: " << lineNumber << " Expected 2 double values separated by a space\n";
				return STATUS_BAD;
			}
			if (weightBuffer < 0) {
				std::cout << "ERROR Line: " << lineNumber << " Expected non-negative values\n";
				return STATUS_BAD;
			}

			file.istream::get();

			weightValuePairs.push_back(std::pair<double, double>(valueBuffer, weightBuffer));
			lineNumber++;
		}

	}


}



void KnapsackProblemUtils::load(string& path, KnapsackProblem& knapsackProblem)
{
	

	std::vector<std::pair<double, double>> weightValuePairs;
	double maxCapacity = 0;

	bool status = loadInstanceFromFile(path, maxCapacity, weightValuePairs);
	
	if (status == STATUS_OK) {
		knapsackProblem = KnapsackProblem(maxCapacity, weightValuePairs);
		std::cout << "Instance of problem from " << path << " was succesfully loaded\n";
	}
	else {
		std::cout << "ERROR: An error has occured while trying to load from " << path << "\n";
	}
}


double KnapsackProblemUtils::findActualBestSolutionFitness(const string& path)
{
	std::vector<std::pair<double, double>> weightValuePairs;
	double maxCapacity = 0;

	bool status = loadInstanceFromFile(path, maxCapacity, weightValuePairs);

	if (status == STATUS_OK) {
		
		return knapSack(maxCapacity, weightValuePairs, weightValuePairs.size());
	}
	else {
		return -1;
	}
}