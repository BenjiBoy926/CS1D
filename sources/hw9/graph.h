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
#include <string>
#include "graph_node.h"

template<typename Key, typename Value>
class graph
{
// PUBLIC TYPEDEFS
public:
	typedef graph_node<Key, Value> node;
	typedef std::function<void(const node&)> node_action;
	typedef typename std::vector<node>::iterator node_iterator;
	typedef typename std::function<bool(const node&)> node_matcher;

// PRIVATE DATA
private:
	std::vector<node> nodes;	// List of graph nodes

// PUBLIC INTERFACE
public:
	// CONSTRUCTORS
	graph<Key, Value>() : nodes() {}

	// Add a node to the graph
	// By default, all nodes in the graph are disconnected.
	// Connections need to be set up via calls to connect methods
	// Return false if the addition did not take place
	bool add(const Key&, const Value&);

	// Find the node with the given key and return it's value
	// Throw exception if no node with the given key exists in the graph
	Value find(const Key&) const throw(std::invalid_argument);

	// Remove a node from the graph
	// Return true if a node was found with the key and false
	// if no key found or removed
	bool remove(const Key&);

	// Clear out all nodes in the graph
	void clear();

	// Make the node with the first key point to the node with the second key
	// Do nothing if the parent already points to child
	// True if the state of the graph was modified
	// The graph is not modified and the function returns false if:
	//		- the edge already exists
	//		- the parent or child key does not exist
	bool add_directed_edge(const Key& parent, const Key& child);

	// Make each node with each key point to each other
	// Do nothing if the nodes already share an undirected edge
	// Return true if the state of the graph was modified
	// The graph is not modified and the function returns false if:
	//		- the edge already exists
	//		- the parent or child key does not exist
	bool add_undirected_edge(const Key& node1, const Key& node2);

	// Given the keys of the beginning node, return a list of nodes in the order that the traversal visited them
	std::vector<node> breadth_first_traversal(const Key& begin) const throw(std::invalid_argument);
	std::vector<node> depth_first_traversal(const Key& begin) const throw(std::invalid_argument);

// PRIVATE HELPERS
private:
	// Find the node with the key and return a pointer to it
	// Throw if no node with the key exists in the graph
	node* find_node(const Key&) const throw(std::invalid_argument);

	// Given a node and a set of keys already visited,
	// return a pointer to the first node in the adjacency list
	// that has not been visited yet.
	// If all adjacent nodes have been visited, return nullptr
	static node* find_first_adjacent_not_visited(const node&, const std::set<Key>& visitedKeys);

	// Return a node finding functor to match the given key
	static node_matcher match_key(const Key&);

	// Search and remove the given node pointer
	// in the adjacency lists of all of the nodes in the graph
	void remove_adjacencies(const node*);
};

template<typename Key, typename Value>
bool graph<Key, Value>::add(const Key& key, const Value& value)
{
	if(nodes.empty())
	{
		nodes.push_back(node(key, value));
		return true;
	}
	else
	{
		auto nodeItor = find_if(nodes.begin(), nodes.end(), match_key(key));

		// If node's key wasn't found, add it to the list
		if(nodeItor == nodes.end())
		{
			nodes.push_back(node(key, value));
			return true;
		}
		// If key already exists, return false
		else
		{
			return false;
		}
	}
}

template<typename Key, typename Value>
Value graph<Key, Value>::find(const Key& key) const throw(std::invalid_argument)
{
	return find_node(key)->get_value();
}

template<typename Key, typename Value>
bool graph<Key, Value>::remove(const Key& key)
{
	if(nodes.empty())
	{
		return false;
	}
	else
	{
		auto nodeItor = find_if(nodes.begin(), nodes.end(), match_key(key));

		// If node's key was found, remove it
		if(nodeItor != nodes.end())
		{
			remove_adjacencies(nodeItor);
			nodes.erase(nodeItor);
			return true;
		}
		// If key doesn't exist, return false
		else
		{
			return false;
		}
	}
}

template<typename Key, typename Value>
void graph<Key, Value>::clear()
{
	nodes.clear();
}

template<typename Key, typename Value>
bool graph<Key, Value>::add_directed_edge(const Key& parent, const Key& child)
{
	// Try to get the parent-child nodes
	// and add directed edge from parent to child
	try
	{
		node* parentItor = find_node(parent);
		node* childItor = find_node(child);

		// Return true if either edge was added
		bool edgeAdded = parentItor->add_directed_edge(childItor);
		return edgeAdded;
	}
	// If either key does not exist, return false
	catch(std::invalid_argument& invArg)
	{
		return false;
	}
}

template<typename Key, typename Value>
bool graph<Key, Value>::add_undirected_edge(const Key& node1, const Key& node2)
{
	return add_directed_edge(node1, node2) || add_directed_edge(node2, node1);
}

template<typename Key, typename Value>
std::vector<typename graph<Key, Value>::node>
graph<Key, Value>::breadth_first_traversal(const Key& begin) const throw(std::invalid_argument)
{
	std::vector<node> traversalOrder;	// List of nodes in order visited
	std::set<Key> nodesVisited;	// Keys of the nodes that have been visited in the traversal
	std::queue<node*> que;
	node* currentNode = find_node(begin);

	do // while(!que.empty())
	{
		traversalOrder.push_back(*currentNode);

		// Push each node adjacent to the current node into the queue
		// if it has not already been visited
		for(int i = 0; i < currentNode->adjacencyList.size(); i++)
		{
			if(nodesVisited.count(currentNode->adjacencyList[i].key) == 0)
			{
				que.push(currentNode->adjacencyList[i]);
			}
		}

		// Pop the next node out of the queue and mark it as visited
		currentNode = que.front();
		nodesVisited.insert(currentNode->key);
		que.pop();

	}while(!que.empty());

	return traversalOrder;
}

template<typename Key, typename Value>
std::vector<typename graph<Key, Value>::node>
graph<Key, Value>::depth_first_traversal(const Key& begin) const throw(std::invalid_argument)
{
	std::vector<node> traversalOrder;	// List of nodes in order visited
	std::set<Key> nodesVisited;	// Keys of the nodes that have been visited in the traversal
	std::stack<node*> stk;
	node* currentNode = &*find_node(begin);
	node* nextNode;	// Next node to visit

	do // while(!stk.empty())
	{
		stk.push(currentNode);
		nodesVisited.insert(currentNode->key);

		nextNode = find_first_adjacent_not_visited(*currentNode, nodesVisited);

		// If all adjacent nodes to the current node have been visited,
		// add current to the traversal order and pop it off of the stack
		if(nextNode == nullptr)
		{
			traversalOrder.push_back(*currentNode);
			stk.pop();

			// If stack isn't empty, empty current node
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

template<typename Key, typename Value>
typename graph<Key, Value>::node*
graph<Key, Value>::find_node(const Key& key) const throw(std::invalid_argument)
{
	if(nodes.empty())
	{
		throw std::invalid_argument("For input key " + std::to_string(key) +
				": you cannot request to search right now because the graph is empty");
	}
	else
	{
		// Return the node with the matching key
		for(unsigned int i = 0; i < nodes.size(); i++)
		{
			if(nodes[i].key == key)
			{
				return (node*)&nodes[i];
			}
		}

		// If key doesn't exist, return false
		throw std::invalid_argument("For input key " + std::to_string(key) +
				": no node with the given key was found in the list");
	}
}

template<typename Key, typename Value>
typename graph<Key, Value>::node*
graph<Key, Value>::find_first_adjacent_not_visited(const node& n, const std::set<Key>& visitedKeys)
{
	for(unsigned int i = 0; i < n.adjacencyList.size(); i++)
	{
		if(visitedKeys.count(n.adjacencyList[i]->key) == 0)
		{
			return n.adjacencyList[i];
		}
	}
	return nullptr;
}

template<typename Key, typename Value>
typename graph<Key, Value>::node_matcher
graph<Key, Value>::match_key(const Key& key)
{
	return [&key](const node& n)
	{
		return key == n.get_key();
	};
}

template<typename Key, typename Value>
void graph<Key, Value>::remove_adjacencies(const node* nodePtr)
{
	for(int i = 0; i < nodes.size(); i++)
	{
		nodes[i].adjacencyList.erase(nodePtr);
	}
}

#endif /* GRAPH_H_ */
