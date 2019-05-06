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
		out << "|--------------------------|"  << endl;
		out << "| Testing inputs from file | " << inputFiles[currentFile] << endl;
		out << "|--------------------------|"  << endl << endl;

		// Run the algorithms and report the results for many different amounts of strings
		for(int currentPartition = 0; currentPartition < totalPartitions; currentPartition++)
		{
			totalElements = maxInputSize * ((float)(currentPartition + 1) / totalPartitions);
			stats = hash_table_analyzer::get_algorithm_stats(table,
					inputFiles[currentFile].c_str(), totalElements);

			out << "--- Testing with " << totalElements << " strings ---" << endl;
			out << "Inserted all in: " << stats.insertAllTime.count() << " milliseconds" << endl;
			out << "Found all in:    " << stats.findAllTime.count() << " milliseconds" << endl;
			out << "Removed all in:  " << stats.removeAllTime.count() << " milliseconds" << endl;
			out << endl;
		}
	}
}

void hash_table_test_application::report_different_hasher_stats(ostream& out,
		const char* filename, int numElements)
{
	hash_table_analyzer::hash_table_stats stats;

	table.set_hasher(bit_shift_hasher());
	stats = hash_table_analyzer::get_all_stats(table, filename, numElements);
	output_hash_table_stats(out, "Bit shift hasher", stats);

	table.set_hasher(sum_hasher());
	stats = hash_table_analyzer::get_all_stats(table, filename, numElements);
	output_hash_table_stats(out, "Summation hasher", stats);

	table.set_hasher(product_hasher());
	stats = hash_table_analyzer::get_all_stats(table, filename, numElements);
	output_hash_table_stats(out, "Product hasher", stats);
}

void hash_table_test_application::output_hash_table_stats(ostream& out, const string& hasherName,
		hash_table_analyzer::hash_table_stats stats)
{
	out << "|------------------|" << endl;
	out << "| Stats for hasher | " << hasherName << endl;
	out << "|------------------|" << endl << endl;

	// Output stats on hash chain stats
	out << "Hash chain stats" << endl;
	out << "\tMaximum length:     " << stats.chainStats.max << endl;
	out << "\tMinimum length:     " << stats.chainStats.min << endl;
	out << "\tAverage length:     " << stats.chainStats.avg << endl;
	out << "\tStandard deviation: " << stats.chainStats.standardDev << endl << endl;

	// Output stats on algorithm stats
	out << "Hash table algorithm performance" << endl;
	out << "\tInsert all: " << stats.algorithmStats.insertAllTime.count() << " milliseconds" << endl;
	out << "\tFind all:   " << stats.algorithmStats.findAllTime.count() << " milliseconds" << endl;
	out << "\tRemove all: " << stats.algorithmStats.removeAllTime.count() << " milliseconds" << endl << endl;
}

hash_table_test_application::hasher
hash_table_test_application::general_hasher()
{
	auto hashFunction = [](const string& key, int maxHash)
	{
		unsigned int hash = 0;
		for(unsigned int i = 0; i < key.size(); i++)
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
		for(unsigned int i = 0; i < key.size(); i++)
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
		for(unsigned int i = 0; i < key.size(); i++)
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
		int result = 0;
		for(unsigned int i = 0; i < key.size(); i++)
		{
			result *= key[i];
		}
		return abs(result) % maxHash;
	};
	return hashFunction;
}

hash_table_test_application::hasher
hash_table_test_application::my_hasher()
{
	auto hash_function = [](const string& key, int maxHash)
	{
		if(key.size() > 0)
		{
			return (int)((key.size() + key.at(0)) % maxHash);
		}
		else
		{
			return (int)(maxHash / 2);
		}
	};
	return hash_function;
}
