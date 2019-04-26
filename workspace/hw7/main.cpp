/*
 * main.cpp
 *
 *  Created on: Apr 21, 2019
 *      Author: creat
 */


#include "insertion_sorter.h"
#include "quick_sorter.h"
#include "heap_sorter.h"
#include <vector>
using namespace std;

const int TOTAL_STRINGS = 45000;	// Total strings in sample input file
const int TOTAL_PARTITIONS = 10;	// Total times
const char* INPUT_FILE = "strings.txt";

int main()
{
	// List of sorting classes
	vector<sorter<string>*> sorters = {
		new insertion_sorter<string>(TOTAL_STRINGS),
		new quick_sorter<string>(TOTAL_STRINGS),
		new heap_sorter<string>(TOTAL_STRINGS)
	};
	// Function object calls "sort and report" on the given sorter
	auto sortAndReport = [](sorter<string>*& sorter) {
		sorter->sort_report();
	};
	// Function object deletes a pointer to a sorter
	auto deleteSorter = [](sorter<string>*& sorter) {
		delete sorter;
	};

	for(int i = 1; i <= TOTAL_PARTITIONS; i++)
	{
		// Initialize each of the sorters from the same file
		auto initializeFromFile = [i](sorter<string>*& sorter) {
			sorter->initialize_from_file(INPUT_FILE, TOTAL_STRINGS * ((float)i / TOTAL_PARTITIONS));
		};
		for_each(sorters.begin(), sorters.end(), initializeFromFile);

		// Output the number of strings being sorted in this partition
		cout << "--- SORTING " << TOTAL_STRINGS * ((float)i / TOTAL_PARTITIONS) << " STRINGS ---" << endl << endl;

		// Sort and report on each of the sorters
		for_each(sorters.begin(), sorters.end(), sortAndReport);
		cout << endl;
	}

	// Delete each of the sorters before exiting
	for_each(sorters.begin(), sorters.end(), deleteSorter);

	return 0;
}
