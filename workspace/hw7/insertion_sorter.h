/*
 * INSERTION SORTER: Time complexity - O(n^2)
 */

#ifndef INSERTION_SORTER_H_
#define INSERTION_SORTER_H_

#include "sorter.h"

// INTERFACE

template<typename Type>
class insertion_sorter : public sorter<Type>
{
public:
	insertion_sorter(int capacity) :
		sorter<Type>(capacity) {}

	void sort();

	void sort_report();

private:
	// Insert the value given in the array in the part [0, end] (inclusive)
	void ordered_insert(int end, Type value);
};

// IMPLEMENTATION

template<typename Type>
void insertion_sorter<Type>::sort()
{
	for(int i = 1; i < this->arrayLen; i++)
	{
		ordered_insert(i, this->array[i]);
	}
}

template<typename Type>
void insertion_sorter<Type>::ordered_insert(int end, Type value)
{
	int insertionIndex = end;

	while(insertionIndex > 0 && this->array[insertionIndex - 1] > value)
	{
		this->array[insertionIndex] = this->array[insertionIndex - 1];
		insertionIndex--;
	}

	this->array[insertionIndex] = value;
}

template<typename Type>
void insertion_sorter<Type>::sort_report()
{
	sorter<Type>::sort_report("Insertion Sort");
}

#endif /* INSERTION_SORTER_H_ */
