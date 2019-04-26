/*
 * quick_sorter.h
 *
 *  Created on: Apr 21, 2019
 *      Author: creat
 */

#ifndef QUICK_SORTER_H_
#define QUICK_SORTER_H_

#include "sorter.h"
#include <algorithm>

// INTERFACE

template<typename Type>
class quick_sorter : public sorter<Type>
{
public:
	quick_sorter(int capacity) :
		sorter<Type>(capacity) {}

	void sort();

	void sort_report();

private:
	// Function recursively called to quicksort the list
	void sort_recursive(int arStart, int arEnd);

	// Perform the partition step of quicksort
	// Take the element at arEnd - 1 as the PIVOT, move all elements bigger
	// than PIVOT above PIVOT and all elements less than PIVOT below PIVOT,
	// and return the new index of the PIVOT
	int partition(int arStart, int arEnd);
};

// IMPLEMENTATION

template<typename Type>
void quick_sorter<Type>::sort()
{
	sort_recursive(0, this->arrayLen);
}

template<typename Type>
void quick_sorter<Type>::sort_report()
{
	sorter<Type>::sort_report("Quick Sort");
}

template<typename Type>
void quick_sorter<Type>::sort_recursive(int start, int end)
{
	if(start < end)
	{
		// Get the pivot
		int pivot = partition(start, end);

		// Repeat quick sort on sub-array above and below the pivot
		sort_recursive(start, pivot - 1);
		sort_recursive(pivot + 1, end);
	}
}

template<typename Type>
int quick_sorter<Type>::partition(int start, int end)
{
	int pivotPos = start;	// Position the pivot will be moved to at the end

	// Loop from the start up to the element before the end
	for(int i = start; i < end - 1; i++)
	{
		// If the current element is less than the element
		// at the end, swap it with the current pivot position
		// and advance the pivot position
		if(this->array[i] < this->array[end - 1])
		{
			std::swap(this->array[i], this->array[pivotPos]);
			pivotPos++;
		}
	}

	// Swap the number at the end with the pivot position found
	std::swap(this->array[pivotPos], this->array[end - 1]);

	return pivotPos;
}


#endif /* QUICK_SORTER_H_ */
