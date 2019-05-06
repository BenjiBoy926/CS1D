/*
 * main.cpp
 *
 *  Created on: Apr 30, 2019
 *      Author: chuntting0
 */

#include "hash_table_test_application.h"
using namespace std;

// Default hash table size
const int TABLE_SIZE = 53;
// Max elements in the input file
const int MAX_INPUT_SIZE = 5000;
const int TOTAL_PARTITIONS = 10;
// Total number of input files
const int TOTAL_INPUT_FILES = 2;
// Input files to receive data to test the hash table
const std::string INPUT_FILES[TOTAL_INPUT_FILES] = {
	"random.txt",
	"words.txt"
};

int main()
{
	hash_table_test_application app(TABLE_SIZE);
	app.report_hash_table_algorithm_stats(cout, INPUT_FILES, TOTAL_INPUT_FILES,
			TOTAL_PARTITIONS, MAX_INPUT_SIZE);
	app.report_different_hasher_stats(cout, "random.txt", MAX_INPUT_SIZE);
	return 0;
}
