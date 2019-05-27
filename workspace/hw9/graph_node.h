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
template<typename Value>
class graph;

template<typename Value>
class graph_node
{
// PUBLIC TYPEDEFS
public:
	typedef std::map<Value, graph_node<Value>*> node_ptr_map;

// PRIVATE DATA
private:
	Value value;	// Value to identify the node
	node_ptr_map adjacencyList;
		// References to the nodes that this node is connected to

// PUBLIC INTERFACE
public:
	// CONSTRUCTORS
	graph_node() : value(), adjacencyList() {}
	graph_node(const Value& value) : value(value), adjacencyList() {}

	// GETTERS
	Value get_value() const { return value; }
	node_ptr_map get_adjacency_list() { return adjacencyList; }

	// "Directed link" - make this node point to the other one
	// Return true if the edge was added and false if not
	bool directed_edge(graph_node<Value>*);

	// "Undirected link" - make each node point to each other
	// Return a pair of bools:
	//		- first indicates if directed edge created this -> other
	//		- second indicates if directed edge created other -> this
	std::pair<bool, bool> undirected_edge(graph_node<Value>*);

	// Disconnect this node from the node with the given value
	// Return true if a node was removed. If the other node
	// also points to this node, that edge remains intact
	bool disconnect(const Value&);

	bool share_directed_edge(const Value&) const;
	bool share_undirected_edge(const Value&) const;

// FRIENDS
	friend class graph<Value>;
	friend class graph_analyzer;
};

template<typename Value>
bool graph_node<Value>::directed_edge(graph_node<Value>* nodePtr)
{
	return adjacencyList.insert(std::pair<Value, graph_node<Value>*>(nodePtr->value, nodePtr)).second;
}

template<typename Value>
std::pair<bool, bool> graph_node<Value>::undirected_edge(graph_node<Value>* nodePtr)
{
	return std::make_pair(this->directed_edge(nodePtr), nodePtr->directed_edge(this));
}

template<typename Value>
bool graph_node<Value>::disconnect(const Value& val)
{
	return adjacencyList.erase(val) > 0;
}

template<typename Value>
bool graph_node<Value>::share_directed_edge(const Value& val) const
{
	return adjacencyList.count(val) > 0;
}

template<typename Value>
bool graph_node<Value>::share_undirected_edge(const Value& val) const
{
	try {
		graph_node<Value>* nodePtr = adjacencyList.at(val);
		return share_directed_edge(val) && nodePtr->share_directed_edge(value);
	}
	catch(std::out_of_range& outRange) {
		return false;
	}
}

#endif /* GRAPH_NODE_H_ */
