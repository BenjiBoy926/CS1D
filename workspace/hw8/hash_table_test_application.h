/*
 * hash_table_test_application.h
 *
 *  Created on: May 1, 2019
 *      Author: chuntting0
 */

#ifndef HASH_TABLE_TEST_APPLICATION_H_
#define HASH_TABLE_TEST_APPLICATION_H_

#include "hash_table_analyzer.h"
#include <chrono>
#include <iostream>

class hash_table_test_application
{
// PUBLIC TYPEDEFS
public:
	typedef typename hash_table<int>::hash_generator hasher;

// PRIVATE DATA
private:
	// The hash table to test
	hash_table<int> table;

public:
	hash_table_test_application(int tableSize) : table(tableSize, general_hasher()) {}

	// Test the functions in the hash table, then test the different hashing functions
	void test_all();

	// Test the functions in the hash table with the general hasher - insertion, finding, and deletion
	void report_hash_table_algorithm_stats(std::ostream&, const std::string* inputFiles,
			int totalInputFiles, int totalPartitions, int maxInputSize);

	// Test the hash table's efficiency given different hashing functions
	void report_different_hasher_stats();

	// Test and report the statistics of using the bit shift hasher
	void test_bit_shift_hasher(const char* filename, int numElements);

	// Test and report the statistics of using the summation hasher
	void test_sum_hasher(const char* filename, int numElements);

	// Test and report the statistics of using the multiplication-based hasher
	void test_product_hasher(const char* filename, int numElements);

	// Output all given stats for the hash function
	void output_hash_table_stats(const std::string& hashFunctionName, int minHashChainLength, int maxHashChainLength,
			int avgHashChainLength, const hash_table_analyzer::hash_table_algorithm_stats& algorithmStats);

public:
	// Different hash functions for the hash table
	static hasher general_hasher();
	static hasher bit_shift_hasher();
	static hasher sum_hasher();
	static hasher product_hasher();
};

#endif /* HASH_TABLE_TEST_APPLICATION_H_ */
