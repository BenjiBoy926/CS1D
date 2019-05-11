/*
 * graph_node.h
 *
 *  Created on: May 11, 2019
 *      Author: creat
 */

#ifndef GRAPH_NODE_H_
#define GRAPH_NODE_H_

#include <vector>
#include <algorithm>
#include <stdexcept>

template<typename Type>
class graph_node
{
// PUBLIC TYPEDEFS
public:
	typedef graph_node<Type> node;

// PRIVATE DATA
private:
	Type value;	// The data at the node
	std::vector<node*> adjacencyList;
		// References to the nodes that this node is connected to

// PUBLIC INTERFACE
public:
	// CONSTRUCTORS
	graph_node(const Type& value) : value(value), adjacencyList() {}

	// GETTERS
	Type& get_value() const { return value; }

	// "Directed link" - make this node point to the other one
	// If this node already points to the other, throw exception
	void dlink(const node*) throw(std::invalid_argument);

	// "Undirected link" - make each node point to each other
	// If one node already points to the other (i.e. they have a directed connection),
	// convert the directed connection to an undirected connection without throwing any errors
	// If the nodes already have an undirected connection, throw an exception
	void ulink(const node*) throw(std::invalid_argument);
};

template<typename Type>
void graph_node<Type>::dlink(const node* nodePtr) throw(std::invalid_argument)
{
	// If adjacency list is empty, add this node to the list
	if(this->adjacencyList.empty())
	{
		this->adjacencyList.push_back(nodePtr);
	}
	// If adjacency list is not empty, check to make sure
	// a reference to this node is not already in the list
	else
	{
		auto comparePointers = [nodePtr](node* otherPtr)
		{
			return nodePtr == otherPtr;
		};
		auto nodeFound = std::find_if(this->adjacencyList.begin(),
				this->adjacencyList.end(), comparePointers);

		// If the node pointer wasn't found, add it to the adjacency list
		if(nodeFound == this->adjacencyList.end())
		{
			this->adjacencyList.push_back(nodeFound);
		}
		// If the node pointer is already in the list, throw an exception
		else
		{
			throw std::invalid_argument(
					"For input node with value " +
					to_string(nodePtr->value) +
					": a reference to this node already exists in the node with value " +
					to_string(this->value));
		}
	}
}

template<typename Type>
void graph_node<Type>::ulink(const node* nodePtr) throw(std::invalid_argument)
{
	bool firstThrew = false;

	// Catch if this is already connected to the other
	try {
		this->dlink(nodePtr);
	}
	catch(std::invalid_argument& invArg) {
		firstThrew = true;
	}

	// Catch if the other already points to this
	try {
		nodePtr->dlink(this);
	}
	catch(std::invalid_argument& invArg) {
		// If this already contained that, and that contains this, throw an exception
		if (firstThrew)
		{
			throw std::invalid_argument(
					"For input node with value " +
					to_string(nodePtr->value) +
					": this and the node with value " +
					to_string(this->value) +
					" already share an undirected connection");
		}
	}
}

#endif /* GRAPH_NODE_H_ */
