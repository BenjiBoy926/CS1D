/*
 * graph.h
 *
 *  Created on: May 13, 2019
 *      Author: chuntting0
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <functional>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <iostream>
#include "graph_node.h"

template<typename Key>
class graph
{
// PUBLIC TYPEDEFS
public:
	typedef graph_node<Key> node;
	typedef std::function<void(const node&)> node_action;
	typedef typename std::vector<node>::iterator node_iterator;
	typedef typename std::function<bool(const node&)> node_matcher;

// PRIVATE DATA
private:
	std::map<Key, node> nodes;	// List of graph nodes

// PUBLIC INTERFACE
public:
	// CONSTRUCTORS
	graph() : nodes() {}

	// Add a node to the graph
	// By default, all nodes in the graph are disconnected.
	// Connections need to be set up via calls to connect methods
	// Return false if the addition did not take place
	bool insert(const Key&);

	// Find the node with the given key and return a pointer to it
	// Throw exception if no node with the given key exists in the graph
	node* at(const Key&) const throw(std::out_of_range);

	// Remove a node from the graph
	// Return true if a node was found with the key and false
	// if no key found or removed
	bool erase(const Key&);

	// Clear out all nodes in the graph
	void clear();

	// Make the node with the first key point to the node with the second key
	// Do nothing if the parent already points to child
	// True if the state of the graph was modified
	// The graph is not modified and the function returns false if:
	//		- the edge already exists
	//		- the parent or child key does not exist
	bool directed_edge(const Key& parent, const Key& child) throw(std::out_of_range);

	// Like directed edge, but adds the node if it does not exist in the graph
	// Bools represent:
	//		- first, whether the parent key had to be added
	//		- second, whether the child key had to be added
	//		- third, whether the edge had to be added
	std::tuple<bool, bool, bool> add_directed_edge(const Key& parent, const Key& child);

	// Make each node with each key point to each other
	// Do nothing if the nodes already share an undirected edge
	// Bools represent which edge had to be added
	//		- first, if node1 -> node2 was added
	//		- second, if node2 -> node1 was added
	std::pair<bool, bool> undirected_edge(const Key& node1, const Key& node2) throw(std::out_of_range);

	// Like undirected edge, but adds the node if it does not exist in the graph
	// Bools represent:
	//		- first, if node1 had to be added
	//		- second, if node2 had to be added
	//		- third, if edge node1 -> node2 was added
	//		- fourth, if edge node2 -> node1 was added
	std::tuple<bool, bool, bool, bool> add_undirected_edge(const Key& node1, const Key& node2);

	// Given the keys of the beginning node, return a list of nodes in the order that the traversal visited them
	std::vector<node> breadth_first_traversal(const Key& begin) const throw(std::out_of_range);
	std::vector<node> depth_first_traversal(const Key& begin) const throw(std::out_of_range);

// PRIVATE HELPERS
private:
	// Given a node and a set of keys already visited,
	// return a pointer to the first node in the adjacency list
	// that has not been visited yet.
	// If all adjacent nodes have been visited, return nullptr
	static node* find_first_adjacent_not_visited(const node&, const std::set<Key>& visitedKeys);

	// Return a node finding functor to match the given key
	static node_matcher match_key(const Key&);

	// Search and remove the given node pointer
	// in the adjacency lists of all of the nodes in the graph
	void remove_adjacencies(const Key&);

// FRIENDS
	friend class graph_analyzer;
};

template<typename Key>
bool graph<Key>::insert(const Key& key)
{
	return nodes.insert(std::pair<Key, node>(key, node(key))).second;
}

template<typename Key>
typename graph<Key>::node*
graph<Key>::at(const Key& key) const throw(std::out_of_range)
{
	return (graph<Key>::node*)&nodes.at(key);
}

template<typename Key>
bool graph<Key>::erase(const Key& key)
{
	remove_adjacencies(key);
	return nodes.erase(key) > 0;
}

template<typename Key>
void graph<Key>::clear()
{
	nodes.clear();
}

template<typename Key>
bool graph<Key>::directed_edge(const Key& parent, const Key& child) throw(std::out_of_range)
{
	node* parentItor = at(parent);
	node* childItor = at(child);

	// Return true if the edge was added
	return parentItor->directed_edge(childItor);
}

template<typename Key>
std::tuple<bool, bool, bool>
graph<Key>::add_directed_edge(const Key& parent, const Key& child)
{
	bool parentAdded;
	bool childAdded;
	bool edgeAdded;

	// Try to add the directed edge.  Exception thrown if either doesn't exist
	try {
		edgeAdded = directed_edge(parent, child);
		return std::make_tuple(false, false, edgeAdded);
	}
	catch(std::out_of_range& invArg) {
		// Add parent and child, and assign to see if they needed to be added
		parentAdded = insert(parent);
		childAdded = insert(child);

		// Add the directed edge
		edgeAdded = directed_edge(parent, child);
		return std::make_tuple(parentAdded, childAdded, edgeAdded);
	}
}

template<typename Key>
std::pair<bool, bool> graph<Key>::undirected_edge(const Key& node1, const Key& node2) throw(std::out_of_range)
{
	node* parentItor = at(node1);
	node* childItor = at(node2);

	// Return true if either edge was added
	return parentItor->undirected_edge(childItor);
}

template<typename Key>
std::tuple<bool, bool, bool, bool>
graph<Key>::add_undirected_edge(const Key& node1, const Key& node2)
{
	bool node1Added;
	bool node2Added;
	std::pair<bool, bool> edgesAdded;

	// Try to add the undirected edges
	// Throws if either node is not in the graph
	try {
		edgesAdded = undirected_edge(node1, node2);
		return std::make_tuple(false, false, edgesAdded.first, edgesAdded.second);
	}
	catch(std::out_of_range& invArg) {
		// Add nodes and grab results
		node1Added = insert(node1);
		node2Added = insert(node2);

		// Add the edge and return the information tuple
		edgesAdded = undirected_edge(node1, node2);
		return std::make_tuple(node1Added, node2Added, edgesAdded.first, edgesAdded.second);
	}
}

template<typename Key>
std::vector<typename graph<Key>::node>
graph<Key>::breadth_first_traversal(const Key& begin) const throw(std::out_of_range)
{
	std::vector<node> traversalOrder;	// List of nodes in order visited
	std::set<Key> nodesVisited;	// Keys of the nodes that have been visited in the traversal
	std::queue<node*> que;
	node* currentNode = at(begin);

	// Visit the first node immediately
	nodesVisited.insert(currentNode->key);

	do // while(!que.empty())
	{
		traversalOrder.push_back(*currentNode);

		// Push each node adjacent to the current node into the queue
		// if it has not already been visited
		for(auto nodePair : currentNode->adjacencyList)
		{
			if(nodesVisited.count(nodePair.first) == 0)
			{
				nodesVisited.insert(nodePair.first);
				que.push(nodePair.second);
			}
		}

		// If there are nodes in the queue, pop out the node at the front
		if(!que.empty())
		{
			currentNode = que.front();
			que.pop();
		}
		// If the queue is empty, assign current node to null pointer
		else
		{
			currentNode = nullptr;
		}

	}while(currentNode != nullptr);

	return traversalOrder;
}

template<typename Key>
std::vector<typename graph<Key>::node>
graph<Key>::depth_first_traversal(const Key& begin) const throw(std::out_of_range)
{
	std::vector<node> traversalOrder;	// List of nodes in order visited
	std::set<Key> nodesVisited;	// Keys of the nodes that have been visited in the traversal
	std::stack<node*> stk;
	node* currentNode = at(begin);
	node* nextNode;	// Next node to visit
	std::pair<class std::set<Key>::iterator, bool> visitedResult;	// Result of inserting a node into visited set

	do // while(!stk.empty())
	{
		// Insert the current node in set of nodes visited
		visitedResult = nodesVisited.insert(currentNode->key);

		// If insertion took place, push current onto the stack
		if(visitedResult.second)
		{
			stk.push(currentNode);
		}

		// Find first node adjacent to current that hasn't been visited
		nextNode = find_first_adjacent_not_visited(*currentNode, nodesVisited);

		// If all adjacent nodes to the current node have been visited,
		// add current to the traversal order and pop it off of the stack
		if(nextNode == nullptr)
		{
			traversalOrder.push_back(*currentNode);
			stk.pop();

			// If stack isn't empty, set current node
			// to the node on the top
			if(!stk.empty())
			{
				currentNode = stk.top();
			}
		}
		// If an unvisited adjacent node is found,
		// set current to that node
		else
		{
			currentNode = nextNode;
		}

	}while(!stk.empty());

	return traversalOrder;
}

template<typename Key>
typename graph<Key>::node*
graph<Key>::find_first_adjacent_not_visited(const node& n, const std::set<Key>& visitedKeys)
{
	for(auto nodePair : n.adjacencyList)
	{
		if(visitedKeys.count(nodePair.first) == 0)
		{
			return nodePair.second;
		}
	}
	return nullptr;
}

template<typename Key>
typename graph<Key>::node_matcher
graph<Key>::match_key(const Key& key)
{
	return [&key](const node& n)
	{
		return key == n.get_key();
	};
}

template<typename Key>
void graph<Key>::remove_adjacencies(const Key& removeKey)
{
	for(auto nodePair : nodes)
	{
		nodePair.second.adjacencyList.erase(removeKey);
	}
}

#endif /* GRAPH_H_ */
