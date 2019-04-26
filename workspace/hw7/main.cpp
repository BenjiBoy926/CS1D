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

const int TOTAL_STRINGS = 5000;	// Total strings in sample input file
const int TOTAL_PARTITIONS = 10;	// Total times the input files are partitioned

const int TOTAL_INPUT_FILES = 2;
const string* INPUT_FILES = new string[TOTAL_INPUT_FILES]{
	"random.txt",
	"words.txt"
};

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

	for(int file = 0; file < TOTAL_INPUT_FILES; file++)
	{
		// Output the file name being sorted
		cout << "--- SORTING FILE NAME \"" << INPUT_FILES[file] << "\" ---" << endl;

		for(int partition = 1; partition <= TOTAL_PARTITIONS; partition++)
		{
			// Initialize each of the sorters from the same file
			auto initializeFromFile = [partition, file](sorter<string>*& sorter) {
				sorter->initialize_from_file(INPUT_FILES[file].c_str(), TOTAL_STRINGS * ((float)partition / TOTAL_PARTITIONS));
			};
			for_each(sorters.begin(), sorters.end(), initializeFromFile);

			// Output the number of strings being sorted in this partition
			cout << "--- SORTING " << TOTAL_STRINGS * ((float)partition / TOTAL_PARTITIONS) << " STRINGS ---" << endl << endl;

			// Sort and report on each of the sorters
			for_each(sorters.begin(), sorters.end(), sortAndReport);
			cout << endl;
		}
	}

	// Delete each of the sorters before exiting
	for_each(sorters.begin(), sorters.end(), deleteSorter);

	return 0;
}
