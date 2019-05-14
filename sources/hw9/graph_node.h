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
#include <utility>

// Forward declaration of friend class graph
template<typename Key, typename Value>
class graph;

template<typename Key, typename Value>
class graph_node
{
// PRIVATE DATA
private:
	Key key;	// Key to identify the node
	Value value;	// The data in the node
	std::vector<graph_node<Key, Value>*> adjacencyList;
		// References to the nodes that this node is connected to

// PUBLIC INTERFACE
public:
	// CONSTRUCTORS
	graph_node(const Key& key, const Value& value) : key(key), value(value), adjacencyList() {}

	// GETTERS
	Key get_key() const { return key; }
	Value get_value() const { return value; }

	// "Directed link" - make this node point to the other one
	// Return true if the edge was added and false if not
	bool add_directed_edge(graph_node<Key, Value>*);

	// "Undirected link" - make each node point to each other
	// Return a pair of bools:
	//		- first indicates if directed edge created this -> other
	//		- second indicates if directed edge created other -> this
	std::pair<bool, bool> add_undirected_edge(graph_node<Key, Value>*);

	// Declare the graph a friend of the node class
	friend class graph<Key, Value>;
};

template<typename Key, typename Value>
bool graph_node<Key, Value>::add_directed_edge(graph_node<Key, Value>* nodePtr)
{
	// If adjacency list is empty, add this node to the list
	if(this->adjacencyList.empty())
	{
		this->adjacencyList.push_back(nodePtr);
		return true;
	}
	// If adjacency list is not empty, check to make sure
	// a reference to this node is not already in the list
	else
	{
		auto comparePointers = [nodePtr](graph_node<Key, Value>* otherPtr)
		{
			return nodePtr == otherPtr;
		};
		auto nodeFound = std::find_if(this->adjacencyList.begin(),
				this->adjacencyList.end(), comparePointers);

		// If the node pointer wasn't found, add it to the adjacency list
		if(nodeFound == this->adjacencyList.end())
		{
			this->adjacencyList.push_back(*nodeFound);
			return true;
		}
		else
		{
			return false;
		}
	}
}

template<typename Key, typename Value>
std::pair<bool, bool> graph_node<Key, Value>::add_undirected_edge(graph_node<Key, Value>* nodePtr)
{
	return std::make_pair(this->add_directed_edge(nodePtr), nodePtr->add_directed_edge(this));
}

#endif /* GRAPH_NODE_H_ */
