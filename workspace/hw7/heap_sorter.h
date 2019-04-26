/*
 * heap_sorter.h
 *
 *  Created on: Apr 23, 2019
 *      Author: creat
 */

#ifndef HEAP_SORTER_H_
#define HEAP_SORTER_H_

#include "sorter.h"

template<typename Type>
class heap_sorter : public sorter<Type>
{
public:
	heap_sorter(int capacity) :
		sorter<Type>(capacity) {}

	// Sort the array list
	void sort();

	void sort_report();

protected:
	// Reorganize the local array as a max heap
	void max_heapify();

	// Heapify the heap represented as rooted at the given index of the array
	void max_heapify(int rootIndex);

	// Max heapify a subsection of the local array rooted at root index
	static void max_heapify(Type* array, int length, int rootIndex);
};

template<typename Type>
void heap_sorter<Type>::sort()
{
	// Reorganize the entire array as a max heap
	max_heapify();

	for(int index = this->arrayLen - 1; index >= 0; index--)
	{
		// Put the root (biggest number) at the end
		std::swap(this->array[0], this->array[index]);

		// Restore max heap properties of the unsorted
		// portion of the array
		max_heapify(this->array, index, 0);
	}
}

template<typename Type>
void heap_sorter<Type>::sort_report()
{
	sorter<Type>::sort_report("Heap Sort");
}

template<typename Type>
void heap_sorter<Type>::max_heapify()
{
	// Reorganize all elements in an array as a max heap
	// by starting at the level above the leaves and heapifying
	// all subtrees up to the root
	for(int index = (this->arrayLen / 2) - 1; index >= 0; index--)
	{
		max_heapify(index);
	}
}

template<typename Type>
void heap_sorter<Type>::max_heapify(int rootIndex)
{
	max_heapify(this->array, this->arrayLen, rootIndex);
}

template<typename Type>
void heap_sorter<Type>::max_heapify(Type* array, int length, int rootIndex)
{
	// Index of the largest element in the parent/children structure
	int largest = rootIndex;

	// Get indeces of left and right child of the
	int leftChild = 2 * rootIndex + 1;
	int rightChild = 2 * rootIndex + 2;

	// If left child exists and is bigger than root, swap with the root
	if(leftChild < length && array[largest] < array[leftChild])
	{
		largest = leftChild;
	}

	// If right child exists and is bigger than the root, swap with the root
	if(rightChild < length && array[largest] < array[rightChild])
	{
		largest = rightChild;
	}

	// Swap the root with the larger child and heapify the subtree at the child
	if(largest != rootIndex)
	{
		std::swap(array[rootIndex], array[largest]);
		max_heapify(array, length, largest);
	}
}

#endif /* HEAP_SORTER_H_ */
