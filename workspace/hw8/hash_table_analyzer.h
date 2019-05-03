/*
 * hash_table_analyzer.h
 *
 *  Created on: May 1, 2019
 *      Author: chuntting0
 */

#ifndef HASH_TABLE_ANALYZER_H_
#define HASH_TABLE_ANALYZER_H_

#include "hash_table.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <algorithm>

class hash_table_analyzer
{
public:

	// Encapsulates info about the hash table's hash chains
	struct hash_table_chain_stats
	{
		int max;
		int min;
		int avg;
		int standardDev;
	};

	// Store the stats for each of the algorithms in the hash table
	struct hash_table_algorithm_stats
	{
		std::chrono::milliseconds insertAllTime;
		std::chrono::milliseconds findAllTime;
		std::chrono::milliseconds removeAllTime;
		int totalItems;
	};

	// Encapsulate all stats about the hash table
	struct hash_table_stats
	{
		hash_table_algorithm_stats algorithmStats;
		hash_table_chain_stats chainStats;
	};

// PUBLIC INTERFACE
public:
	// Test all of the algorithms on the given hash table and return a struct with all the report data
	template<typename Type>
	static hash_table_algorithm_stats test_each_algorithm(hash_table<Type>&,
			const char* filename, int numElements);

	// Insert the number of string keys from the file name and return the time it takes
	template<typename Type>
	static std::chrono::milliseconds insert_all(hash_table<Type>&,
			const std::vector<std::string>& keys);

	// Find every string in the file name and return the time it takes
	template<typename Type>
	static std::chrono::milliseconds find_all(const hash_table<Type>&,
			const std::vector<std::string>& keys);

	// Remove every string in the file name and return the time it takes
	template<typename Type>
	static std::chrono::milliseconds remove_all(hash_table<Type>&,
			const std::vector<std::string>& keys);

	// Return a struct containing all stats about the hash chains in the given hash table
	template<typename Type>
	hash_table_chain_stats get_hash_chain_stats(const hash_table<Type>&);

	// Analyze hash chain lengths
	template<typename Type>
	static int min_hash_chain_length(const hash_table<Type>&);

	template<typename Type>
	static int max_hash_chain_length(const hash_table<Type>&);

	template<typename Type>
	static int avg_hash_chain_length(const hash_table<Type>&);

	template<typename Type>
	static int standard_dev_hash_chain_length(const hash_table<Type>&);

// PROTECTED UTILITIES
protected:
	template<typename Type>
	static int total_hash_chain_lengths(const hash_table<Type>&);

	static std::vector<std::string> get_strings_from_file(const char* filename, int numElements);
};

template<typename Type>
hash_table_analyzer::hash_table_algorithm_stats
hash_table_analyzer::test_each_algorithm(hash_table<Type>& table,
		const char* filename, int numElements)
{
	std::vector<std::string> keys = get_strings_from_file(filename, numElements);

	// Get all the stats and return it
	hash_table_algorithm_stats stats;
	stats.insertAllTime = insert_all(table, keys);
	stats.findAllTime = find_all(table, keys);
	stats.removeAllTime = remove_all(table, keys);
	stats.totalItems = numElements;
	return stats;
}

template<typename Type>
std::chrono::milliseconds
hash_table_analyzer::insert_all(hash_table<Type>& table,
		const std::vector<std::string>& keys)
{
	auto insert = [&table](const std::string& key)
	{
		table.insert(key, Type());
	};

	// Get time before and after inserting all strings
	auto begin = std::chrono::system_clock::now();
	std::for_each(keys.begin(), keys.end(), insert);
	auto end = std::chrono::system_clock::now();

	// Return time difference
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
}

template<typename Type>
std::chrono::milliseconds
hash_table_analyzer::find_all(const hash_table<Type>& table,
		const std::vector<std::string>& keys)
{
	auto find = [&table](const std::string& key)
	{
		try {
			table.find(key);
		}
		catch(std::invalid_argument& invError) {
			std::cerr << "Did not find key " << key << std::endl;
		}
	};

	// Get time before and after inserting all strings
	auto begin = std::chrono::system_clock::now();
	std::for_each(keys.begin(), keys.end(), find);
	auto end = std::chrono::system_clock::now();

	// Return time difference
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
}

template<typename Type>
std::chrono::milliseconds
hash_table_analyzer::remove_all(hash_table<Type>& table,
		const std::vector<std::string>& keys)
{
	auto remove = [&table](const std::string& key)
	{
		try {
			table.remove(key);
		}
		catch(std::invalid_argument& invError) {
			std::cerr << "Did not find key " << key << std::endl;
		}
	};

	// Get time before and after inserting all strings
	auto begin = std::chrono::system_clock::now();
	std::for_each(keys.begin(), keys.end(), remove);
	auto end = std::chrono::system_clock::now();

	// Return time difference
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
}

#endif /* HASH_TABLE_ANALYZER_H_ */
