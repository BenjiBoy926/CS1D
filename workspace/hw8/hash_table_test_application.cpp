/*
 * hash_table_test_application.cpp
 *
 *  Created on: May 1, 2019
 *      Author: chuntting0
 */

#include "hash_table_test_application.h"
using namespace std;

void hash_table_test_application::report_hash_table_algorithm_stats(ostream& out,
		const string* inputFiles, int totalInputFiles, int totalPartitions, int maxInputSize)
{
	// Stats for the efficiency of the hash table algorithms
	hash_table_analyzer::hash_table_algorithm_stats stats;
	int totalElements;	// Total elements to test the hash table

	// Set the hasher to use the general hasher
	table.set_hasher(general_hasher());

	for(int currentFile = 0; currentFile < totalInputFiles; currentFile++)
	{
		// Output the name of the file being tested
		out << "|--------------------------------|"  << endl;
		out << "| Testing inputs from file name: | " << inputFiles[currentFile] << endl;
		out << "|--------------------------------|"  << endl << endl;

		// Run the algorithms and report the results for many different amounts of strings
		for(int currentPartition = 0; currentPartition < totalPartitions; currentPartition++)
		{
			totalElements = maxInputSize * ((float)(currentPartition + 1) / totalPartitions);
			stats = hash_table_analyzer::test_each_algorithm(table,
					inputFiles[currentFile].c_str(), totalElements);

			out << "--- Testing with " << totalElements << " strings ---" << endl;
			out << "Inserted all in: " << stats.insertAllTime.count() << " milliseconds" << endl;
			out << "Found all in:    " << stats.findAllTime.count() << " milliseconds" << endl;
			out << "Removed all in:  " << stats.removeAllTime.count() << " milliseconds" << endl;
			out << endl;
		}
	}
}

hash_table_test_application::hasher
hash_table_test_application::general_hasher()
{
	auto hashFunction = [](const string& key, int maxHash)
	{
		unsigned int hash = 0;
		for(int i = 0; i < key.size(); i++)
		{
			hash = (127 * hash + key[i]) % 16908799;
		}
		return hash % maxHash;
	};
	return hashFunction;
}

hash_table_test_application::hasher
hash_table_test_application::bit_shift_hasher()
{
	auto hashFunction = [](const string& key, int maxHash)
	{
		const unsigned int shift = 6;
		const unsigned int zero = 0;
		unsigned int mask = ~zero >> (32 - shift);
		unsigned int result = 0;
		for(int i = 0; i < key.size(); i++)
		{
			result = (result << shift) | (key[i] & mask);
		}
		return result % maxHash;
	};
	return hashFunction;
}

hash_table_test_application::hasher
hash_table_test_application::sum_hasher()
{
	auto hashFunction = [](const string& key, int maxHash)
	{
		int result = 0;
		for(int i = 0; i < key.size(); i++)
		{
			result += key[i];
		}
		return abs(result) % maxHash;
	};
	return hashFunction;
}

hash_table_test_application::hasher
hash_table_test_application::product_hasher()
{
	auto hashFunction = [](const string& key, int maxHash)
	{
		int result;
		for(int i = 0; i < key.size(); i++)
		{
			result *= key[i];
		}
		return abs(result) % maxHash;
	};
	return hashFunction;
}
