/*
 * sort.h
 *
 *  Created on: Apr 17, 2019
 *      Author: chuntting0
 */

#ifndef SORTER_H_
#define SORTER_H_

#include <ctime>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>

// INTERFACE

template<typename Type>
class sorter
{
protected:
	Type* array;	// Array of strings to sort
	int arrayLen;	// Current number of initialized elements in the array
	int arrayCapacity;	// Capacity of the array

public:
	// CONSTRUCTORS
	// Initialize the sorter with the given capacity of objects in its array
	sorter(int capacity);

	// Sort the list and return the number of seconds it took to complete
	std::chrono::seconds timed_sort();

	// Sort the list using operator<
	virtual void sort() = 0;

	// Sort the list and report the time it took
	virtual void sort_report() = 0;

	// Print the list
	void print(std::ostream& out) const;

	// Initialize all elements in the array from the file with the given name
	void initialize_from_file(const char* filename, int numToLoad);

	virtual ~sorter() { delete [] array; }

protected:
	// Sort the list and output the time it took to the console
	void sort_report(std::string sortType);

	template<typename SType>
	friend std::ostream& operator<<(std::ostream& out, const sorter<SType>&);
};

// IMPLEMENTATION

template<typename Type>
sorter<Type>::sorter(int capacity)
{
	array = new Type[capacity];
	arrayLen = 0;
	arrayCapacity = capacity;
}

template<typename Type>
std::chrono::seconds sorter<Type>::timed_sort()
{
	auto begin = std::chrono::system_clock::now();
	sort();
	auto end = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::seconds>(end - begin);
}

template<typename Type>
void sorter<Type>::sort_report(std::string sortType)
{
	// Output the result
	std::cout << std::setfill('-') << std::left;
	std::cout << std::setw(23) << (sortType + ":") << ">: completed in " << timed_sort().count() << " seconds" << std::endl;
	std::cout << std::setfill(' ') << std::right;
}

template<typename Type>
void sorter<Type>::print(std::ostream& out) const
{
	for(int i = 0; i < arrayLen; i++)
	{
		out << array[i];
		out << std::endl;
	}
}

template<typename Type>
std::ostream& operator<<(std::ostream& out, const sorter<Type>& sort)
{
	sort.print(out);
	return out;
}

template<typename Type>
void sorter<Type>::initialize_from_file(const char* filename, int numToLoad)
{
	std::ifstream fin;
	fin.open(filename);

	if(fin.is_open() && numToLoad <= arrayCapacity)
	{
		for(int i = 0; i < numToLoad; i++)
		{
			fin >> array[i];
		}

		// Make the array len the correct amount
		arrayLen = numToLoad;
	}
}


#endif /* SORTER_H_ */
