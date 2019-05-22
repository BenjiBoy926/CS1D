/*
 * graph_node.h
 *
 *  Created on: May 11, 2019
 *      Author: creat
 */

#ifndef GRAPH_NODE_H_
#define GRAPH_NODE_H_

#include <map>
#include <algorithm>
#include <stdexcept>
#include <utility>
#include <iostream>
#include <sstream>

// Forward declaration of friend class graph
template<typename Key>
class graph;

template<typename Key>
class graph_node
{
// PRIVATE DATA
private:
	Key key;	// Key to identify the node
	std::map<Key, graph_node<Key>*> adjacencyList;
		// References to the nodes that this node is connected to

// PUBLIC INTERFACE
public:
	// CONSTRUCTORS
	graph_node(const Key& key) : key(key), adjacencyList() {}

	// GETTERS
	Key get_key() const { return key; }
	std::map<Key, graph_node<Key>*> get_adjacency_list() { return adjacencyList; }

	// "Directed link" - make this node point to the other one
	// Return true if the edge was added and false if not
	bool directed_edge(graph_node<Key>*);

	// "Undirected link" - make each node point to each other
	// Return a pair of bools:
	//		- first indicates if directed edge created this -> other
	//		- second indicates if directed edge created other -> this
	std::pair<bool, bool> undirected_edge(graph_node<Key>*);

// FRIENDS
	friend class graph<Key>;
	friend class graph_analyzer;
};

template<typename Key>
bool graph_node<Key>::directed_edge(graph_node<Key>* nodePtr)
{
	return adjacencyList.insert(std::pair<Key, graph_node<Key>*>(nodePtr->key, nodePtr)).second;
}

template<typename Key>
std::pair<bool, bool> graph_node<Key>::undirected_edge(graph_node<Key>* nodePtr)
{
	return std::make_pair(this->directed_edge(nodePtr), nodePtr->directed_edge(this));
}

#endif /* GRAPH_NODE_H_ */
