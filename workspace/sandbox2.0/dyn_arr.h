/*
 * dyn_arr.h
 *
 *  Created on: Jan 24, 2019
 *      Author: chuntting0
 */

#ifndef DYN_ARR_H_
#define DYN_ARR_H_

#include <iostream>
#include <iomanip>

template<class T>
class dyn_arr
{
private:
	const static int DEFAULT_INIT_CAPACITY = 8;

	T* arr;
	int size;
	int capacity;
public:
	dyn_arr(int initCapacity = DEFAULT_INIT_CAPACITY) :
		arr{new T[initCapacity]}, size{0}, capacity{initCapacity}
		{};

	// Add a value to the array
	void add(const T& val)
	{
		// If size is equal to capacity, allocate more memory for the array
		if(size >= capacity)
		{
			alloc(capacity * 2);
		}

		// Assign the value to the last element
		arr[size] = val;
		size++;
	}

	// Allocate a bigger array for the dynamic array
	void alloc(int increase)
	{
		if(increase > 0)
		{
			// Allocate new array with increased capacity
			T* newArr = new T[capacity + increase];

			// Assign old elements to new elements
			for(int i = 0; i < size; i++)
			{
				newArr[i] = arr[i];
			}

			// Deallocate old array and assign it to the new one
			delete [] arr;
			arr = newArr;
			capacity += increase;
		}
	}
	// Print the contents of the array to the output stream specified
	void print(std::ostream& out)
	{
		for(int i = 0; i < size; i++)
		{
			out << arr[i];
		}
	}

	~dyn_arr()
	{
		if(arr != nullptr)
		{
			delete [] arr;
		}
	}
};


#endif /* DYN_ARR_H_ */
