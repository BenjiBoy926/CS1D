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

	// Test the functions in the hash table with the general hasher - insertion, finding, and deletion
	void report_hash_table_algorithm_stats(std::ostream&, const std::string* inputFiles,
			int totalInputFiles, int totalPartitions, int maxInputSize);

	// Test the hash table's efficiency given different hashing functions
	void report_different_hasher_stats(std::ostream&, const char*, int numElements);

	// Output all given stats for the hash function
	void output_hash_table_stats(std::ostream&, const std::string& hasherName,
			hash_table_analyzer::hash_table_stats stats);
protected:
	// Different hash functions for the hash table
	static hasher general_hasher();
	static hasher bit_shift_hasher();
	static hasher sum_hasher();
	static hasher product_hasher();
	static hasher my_hasher();
};

#endif /* HASH_TABLE_TEST_APPLICATION_H_ */
