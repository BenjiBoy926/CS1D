/*
 * graph.h
 *
 *  Created on: May 13, 2019
 *      Author: chuntting0
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <functional>
#include "graph_node.h"

enum class graph_traversal_type
{
	BREADTH_FIRST,
	DEPTH_FIRST
};

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
	graph_traversal_type defaultTraversalType;

// PUBLIC INTERFACE
public:
	// CONSTRUCTORS
	graph<Key, Value>() : nodes(), defaultTraversalType(graph_traversal_type::BREADTH_FIRST) {}
	graph<Key, Value>(graph_traversal_type type) : nodes(), defaultTraversalType(type) {}

	// GETTERS/SETTERS
	graph_traversal_type get_default_traversal_type() const { return defaultTraversalType; }
	void set_default_traversal_type(graph_traversal_type type) { defaultTraversalType = type; }

	// Add a node to the graph
	// By default, all nodes in the graph are disconnected.
	// Connections need to be set up via calls to connect methods
	// Throws exception if the key already exists in the list
	void add(const Key&, const Value&) throw(std::invalid_argument);

	// Find the node with the given key and return it's value
	// Throw exception if no node with the given key exists in the graph
	Value find(const Key&) const throw(std::invalid_argument);

	// Remove a node from the graph
	// Return true if a node was found with the key and false
	// if no key found or removed
	bool remove(const Key&);

	// Make the node with the first key point to the node with the second key
	// Throw exceptions if the nodes already share a link, or if either node
	// does not exist in the graph
	void directed_link(const Key& parent, const Key& child) throw(std::invalid_argument);

	// Make each node with each key point to each other
	// Throw exception if the nodes already point to each other,
	// or if either node does not exist in the list
	void undirected_link(const Key& node1, const Key& node2) throw(std::invalid_argument);

// PRIVATE HELPERS
private:
	// Search the node with the given key and return a pointer to it
	// Throw an exception if the node was not found
	node* breadth_first_search(const Key&) const throw(std::invalid_argument);
	node* depth_first_search(const Key&) const throw(std::invalid_argument);

	// Traverse all nodes, performing the given action on each one
	void breadth_first_traversal(node_action) const;
	void depth_first_traversal(node_action) const;

	// Return a node finding functor to match the given key
	static node_matcher match_key(const Key&);
};

template<typename Key, typename Value>
void graph<Key, Value>::add(const Key& key, const Value& value)
{
	if(nodes.empty())
	{
		nodes.push_back(node(key, value));
	}
	else
	{
		auto nodeItor = find_if(nodes.begin(), nodes.end(), match_key(key));

		// If node's key wasn't found, add it to the list
		if(nodeItor == nodes.end())
		{
			nodes.push_back(node(key, value));
		}
		// If key already exists, throw an exception
		else
		{
			throw std::invalid_argument(
					"For input node data " + to_string(key) + to_string(value) +
					": this key already exists in the graph");
		}
	}
}

template<typename Key, typename Value>
Value graph<Key, Value>::find(const Key& key) const throw(std::invalid_argument)
{
	if(nodes.empty())
	{
		throw std::invalid_argument("For input key " + to_string(key) +
				": you cannot request to search right now because the graph is empty");
	}
	else
	{
		auto nodeItor = find_if(nodes.begin(), nodes.end(), match_key(key));

		// If node's key was found, remove it
		if(nodeItor != nodes.end())
		{
			return nodeItor->get_value();
		}
		// If key doesn't exist, return false
		else
		{
			throw std::invalid_argument("For input key " + to_string(key) +
					": no node with the given key was found in the list");
		}
	}
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
graph<Key, Value>::node_matcher
graph<Key, Value>::match_key(const Key& key)
{
	return [&key](const node& n)
	{
		return key == n.get_key();
	};
}

#endif /* GRAPH_H_ */
