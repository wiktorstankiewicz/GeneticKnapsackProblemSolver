#pragma once
#include "MyRandomLib.h"


namespace MyRandomLib {
	namespace _MyRandomLib {
		bool wasInitialized = false;

		void initialize() {
			srand(time(NULL));
			wasInitialized = true;
		}

		void initializeIfNecessary()
		{
			if (!wasInitialized) {
				initialize();
			}
		}
	}


	int randomIntInclusive(int from, int to) {
		_MyRandomLib::initializeIfNecessary();
		return rand() % (to - from + 1) + from;
	}

	double randomDoubleInclusive(const double from, const double to)
	{
		_MyRandomLib::initializeIfNecessary();
		double value = (double)rand() / RAND_MAX;
		return from + value * (to - from);
	}

}