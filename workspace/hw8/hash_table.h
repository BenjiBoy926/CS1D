/*
 * hash_table.h
 *
 *  Created on: Apr 30, 2019
 *      Author: chuntting0
 */

#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <vector>
#include <string>
#include <exception>
#include <functional>
#include <algorithm>
#include <iostream>

// Simple struct to encapsulate a key-value pair for the hash table
template<typename Type>
struct hash_kvp
{
	std::string key;
	Type value;
	hash_kvp(std::string key, Type value) : key(key), value(value) {}
};

template<typename Type>
class hash_table
{
	// Allow analyzer full access to the hash table
	friend class hash_table_analyzer;

// PUBLIC TYPEDEFS
public:
	typedef hash_kvp<Type> hash;
	typedef std::vector<hash> hash_chain;
	typedef typename std::vector<hash>::iterator hash_iterator;
	typedef std::function<bool(hash)> hash_matcher;
	typedef std::function<bool(const std::string&, int)> hash_generator;

// PRIVATE DATA
private:
	// The hash table is an array where each element is itself a chain
	// of key-value pairs that map to the same hash value
	hash_chain* table;
	// Capacity of the array of hash chains
	int size;
	// Function used to generate the hashes for each hash kvp
	hash_generator hasher;

// PUBLIC INTERFACE
public:
	// Construct the hash table with the given size and given hash-generator
	hash_table(int size, hash_generator hasher);

	// Setup a new hash generator for the hash table
	void set_hasher(hash_generator hasher) { this->hasher = hasher; }

	// Insert a kvp into the hash table
	void insert(const std::string&, const Type&);

	// Find the value associated with the key
	Type& find(const std::string&) const;

	// Remove a kvp from the hash table
	void remove(const std::string&);

	// Return the value at the associated key
	Type& operator[](const std::string&) const;

	// Release resources allocated for the hash table
	~hash_table() { delete [] table; }

// PROTECTED UTILITIES
protected:
	// Get the hash chain stored at the given key
	hash_chain& get_hash_chain(const std::string&) const;

	// Return a function object that returns true if the given hash matches the given key
	static hash_matcher match_key(const std::string&);
};

template<typename Type>
hash_table<Type>::hash_table(int size, hash_generator hasher)
{
	this->table = new hash_chain[size];
	this->size = size;
	this->hasher = hasher;
}

// Add the key-value pair to the vector at the hash calculated for the key
template<typename Type>
void hash_table<Type>::insert(const std::string& key, const Type& value)
{
	hash_chain& chain = this->get_hash_chain(key);

	// If the chain is empty, add the hash specified
	if(chain.empty()) {
		chain.push_back(hash(key, value));
	}
	// If the chain is not empty, check to make sure the key doesn't already exist
	else {
		hash_iterator hashValue = std::find_if(chain.begin(), chain.end(), match_key(key));

		// Insert only if the key does not already exist in the hash table
		if(hashValue == chain.end()) {
			chain.push_back(hash(key, value));
		}
		else {
			throw std::invalid_argument("For input key " + key + ": a value is already associated with this key");
		}
	}
}

template<typename Type>
Type& hash_table<Type>::find(const std::string& key) const
{
	return (*this)[key];
}

template<typename Type>
void hash_table<Type>::remove(const std::string& key)
{
	hash_chain& chain = this->get_hash_chain(key);

	// If the chain is empty, add the hash specified
	if(chain.empty()) {
		throw std::invalid_argument("For input key " + key + ": no such key exists in the hash table");
	}
	// If the chain is not empty, check to make sure the key doesn't already exist
	else {
		hash_iterator hashValue = std::find_if(chain.begin(), chain.end(), match_key(key));

		// Insert only if the key does not already exist in the hash table
		if(hashValue == chain.end()) {
			throw std::invalid_argument("For input key " + key + ": no such key exists in the hash table");
		}
		else {
			std::remove_if(chain.begin(), chain.end(), match_key(key));
		}
	}
}

template<typename Type>
Type& hash_table<Type>::operator [](const std::string& key) const
{
	hash_chain hashChain = get_hash_chain(key);

	// If hash chain is not empty, search it for the given key
	if(!hashChain.empty()) {
		hash_iterator iterator = find_if(hashChain.begin(), hashChain.end(), match_key(key));

		// If an iterator was found, return its value
		if(iterator != hashChain.end())
		{
			return iterator->value;
		}
		// If no iterator was found, throw an exception
		else
		{
			throw std::invalid_argument("For input key " + key + ": no such key exists in the hash table");
		}
	}
	// If the hash chain found has no hashes, throw an exception
	else {
		throw std::invalid_argument("For input key " + key + ": no such key exists in the hash table");
	}
}

template<typename Type>
typename hash_table<Type>::hash_chain&
hash_table<Type>::get_hash_chain(const std::string& key) const
{
	return this->table[this->hasher(key, this->size)];
}

template<typename Type>
typename hash_table<Type>::hash_matcher
hash_table<Type>::match_key(const std::string& key)
{
	return [&key](const hash& hashValue){ return hashValue.key == key; };
}

#endif /* HASH_TABLE_H_ */
