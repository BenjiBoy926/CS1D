/*
 * main.cpp
 *
 *  Created on: Apr 30, 2019
 *      Author: chuntting0
 */

#include "hash_table_test_application.h"
using namespace std;

// Default hash table size
const int TABLE_SIZE = 5000;
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
	hash_table<int> table(TABLE_SIZE, hash_table_test_application::general_hasher());

	table.insert("Codey", 22);
	table.insert("Corey", 24);
	table.insert("Carissa", 20);

	cout << "Found value " << table.find("Codey") << endl;
	cout << "Found value " << table.find("Corey") << endl;
	cout << "Found value " << table.find("Carissa") << endl;

	table.remove("Codey");

	try
	{
		int i = table.find("Codey");
		cout << "Found value " << i << endl;
	}
	catch(invalid_argument& invError)
	{
		cout << "Could not find value with key Codey" << endl;
	}

	table.insert("Codey", 65);

	return 0;
}
