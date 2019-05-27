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
#include <sstream>
#include "graph_node.h"

template<typename Key>
class graph
{
// PUBLIC TYPEDEFS
public:
	typedef graph_node<Key> node;
	typedef std::map<Key, node> node_map;
	typedef std::vector<node_map> node_mesh;

// PRIVATE DATA
private:
	node_map nodes;	// List of graph nodes

// PUBLIC INTERFACE
public:
	// CONSTRUCTORS
	graph() : nodes() {}
	graph(const graph<Key>& other) : nodes(other.nodes) {}
	graph(graph<Key>&& other) : nodes(other.nodes) {}

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

	// Return true if the graph contains the key
	bool contains(const Key&) const;

	// Return a graph that is the transpose of this graph
	graph<Key> transpose() const;

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

	// Find the minimum distance between two nodes
	// Throws exception if the either key doesn't exist in the list
	// Return -1 if no path exists between the nodes
	int distance(const Key& begin, const Key& end) const throw(std::out_of_range);

	// Return a list of all of the strongly connected components in the graph
	node_mesh strongly_connected_components() const;

	// Given the keys of the beginning node, return a list of nodes in the order that the traversal visited them
	node_mesh breadth_first_traversal(const Key& begin) const throw(std::out_of_range);
	std::vector<node> depth_first_traversal(const Key& begin) const throw(std::out_of_range);
	std::vector<node> depth_first_traversal(const Key& begin, std::set<Key>& visited) const throw(std::out_of_range);

	/*
	 * STRINGS
	 */
	std::string node_list() const;
	std::string node_adjacency_list(const Key&) const;
	std::string full_node_adjacency_list() const;
	static std::string node_mesh_list(const node_mesh&);

// PRIVATE HELPERS
private:
	// Given a pointer to a node and a set of visited node keys,
	// enqueue all nodes adjacent to the given node whose keys
	// are not in the set.  Return number enqueued
	static int enqueue_unvisited_adjacencies(const node*, std::set<Key>&, std::queue<node*>&);

	// Pop a node out of the given queue and reduce the number of nodes in the current layer by 1
	// If there are no more nodes in the current layer, increment current layer
	static node* dequeue_node(std::queue<node*>&, int& nodesInLayer, int& currentLayer);

	// Given a node and a set of keys already visited,
	// return a pointer to the first node in the adjacency list
	// that has not been visited yet.
	// If all adjacent nodes have been visited, return nullptr
	static node* find_first_adjacent_not_visited(const node&, const std::set<Key>& visitedKeys);

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
bool graph<Key>::contains(const Key& key) const
{
	return nodes.count(key) > 0;
}

template<typename Key>
graph<Key> graph<Key>::transpose() const
{
	graph<Key> trans(*this);
	node* current;
	std::vector<node*> adjacencies;

	// Keeps track of the edges that have been transposed
	std::set<std::pair<Key, Key>> transposedEdges;

	for(auto itor = trans.nodes.begin(); itor != trans.nodes.end(); itor++)
	{
		current = &trans.nodes.at(itor->first);

		// Add adjacencies to the local list
		for(auto kvp : current->adjacencyList)
		{
			adjacencies.push_back(kvp.second);
		}

		// Switch all edges between current node and adjacent nodes
		for(auto adjacent : adjacencies)
		{
			// If the current's connection with the adjacent is not undirected,
			// and has not been transposed before, transpose it
			if(!current->share_undirected_edge(adjacent->get_value()) &&
					transposedEdges.count(std::pair<Key, Key>(current->get_value(), adjacent->get_value())) == 0 &&
					transposedEdges.count(std::pair<Key, Key>(adjacent->get_value(), current->get_value())) == 0)
			{
				current->disconnect(adjacent->get_value());
				trans.directed_edge(adjacent->get_value(), current->get_value());

				// List this as a transposed edge
				transposedEdges.insert(std::pair<Key, Key>(current->get_value(), adjacent->get_value()));
			}
		}

		// Clear out temp list of adjacencies
		adjacencies.clear();
	}

	return trans;
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
int graph<Key>::distance(const Key& begin, const Key& end) const throw(std::out_of_range)
{
	// If the graph does not contain the end node, throw exception
	if(!contains(end))
	{
		throw std::out_of_range(std::string("For argument ") + std::to_string(end) +
				" to function \"graph<Key>::distance\": the graph does not contain this key");
	}

	node_mesh mesh = breadth_first_traversal(begin);

	// Search for the destination key at each level in the mesh
	for(unsigned int i = 0; i < mesh.size(); i++)
	{
		if(mesh[i].count(end) > 0)
		{
			return i;
		}
	}
	return -1;
}

template<typename Key>
typename graph<Key>::node_mesh
graph<Key>::strongly_connected_components() const
{
	std::vector<node> stack = depth_first_traversal(nodes.begin()->second.get_value());
	graph<Key> trans = transpose();

	node_mesh scc(nodes.size());
	std::vector<node> component;
	std::set<Key> visitedNodes;
	node current;
	int totalSCC = 0;

	while(!stack.empty())
	{
		current = stack.back();
		stack.pop_back();

		// If this node hasn't been visited, perform a dfs starting there
		if(visitedNodes.count(current.get_value()) == 0)
		{
			// Do a depth-first traversal, starting at the current node
			component = trans.depth_first_traversal(current.get_value(), visitedNodes);

			// Add each node in the component from the dfs to the list
			for(node n : component)
			{
				scc.at(totalSCC).insert(std::pair<Key, node>(n.get_value(), n));
			}
			totalSCC++;
		}
	}

	scc.resize(totalSCC);
	return scc;
}

template<typename Key>
typename graph<Key>::node_mesh
graph<Key>::breadth_first_traversal(const Key& begin) const throw(std::out_of_range)
{
	node_mesh traversalOrder(nodes.size());	// List of nodes in order visited
	std::set<Key> nodesVisited;	// Keys of the nodes that have been visited in the traversal
	std::queue<node*> que;

	node* currentNode = at(begin);
	int currentLayer = 0;
	std::vector<int> queuedInLayer(nodes.size());

	// Visit the first node immediately
	nodesVisited.insert(currentNode->get_value());

	do // while(currentNode != nullptr)
	{
		traversalOrder.at(currentLayer).insert(std::pair<Key, node>(currentNode->get_value(), *currentNode));

		// Push each node adjacent to the current node into the queue
		// if it has not already been visited
		queuedInLayer.at(currentLayer + 1) += enqueue_unvisited_adjacencies(currentNode, nodesVisited, que);

		// If there are nodes in the queue, pop out the node at the front
		if(!que.empty())
		{
			currentNode = que.front();
			que.pop();

			// If no more nodes in the current layer are waiting in the queue,
			// increment to start inserting nodes into the next layer
			if(queuedInLayer[currentLayer] <= 0)
			{
				currentLayer++;
			}

			// Decrement the number of nodes queued at the current layer
			queuedInLayer[currentLayer]--;
		}
		// If the queue is empty, assign current node to null pointer
		else
		{
			currentNode = nullptr;
		}

	}while(currentNode != nullptr);

	traversalOrder.resize(currentLayer + 1);
	return traversalOrder;
}

template<typename Key>
std::vector<typename graph<Key>::node>
graph<Key>::depth_first_traversal(const Key& begin) const throw(std::out_of_range)
{
	std::set<Key> nodesVisited;	// Keys of the nodes that have been visited in the traversal
	return depth_first_traversal(begin, nodesVisited);
}

template<typename Key>
std::vector<typename graph<Key>::node>
graph<Key>::depth_first_traversal(const Key& begin, std::set<Key>& visited) const throw(std::out_of_range)
{
	std::vector<node> traversalOrder;	// List of nodes in order visited
	std::stack<node*> stk;
	node* currentNode = at(begin);
	node* nextNode;	// Next node to visit
	std::pair<class std::set<Key>::iterator, bool> visitedResult;	// Result of inserting a node into visited set

	do // while(!stk.empty())
	{
		// Insert the current node in set of nodes visited
		visitedResult = visited.insert(currentNode->get_value());

		// If insertion took place, push current onto the stack
		if(visitedResult.second)
		{
			stk.push(currentNode);
			//std::cout << "Pushing node " << currentNode->get_value() << " onto the stack" << std::endl;
		}

		// Find first node adjacent to current that hasn't been visited
		nextNode = find_first_adjacent_not_visited(*currentNode, visited);

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
				//std::cout << "Popped node " << currentNode->get_value() << std::endl;
			}
		}
		// If an unvisited adjacent node is found,
		// set current to that node
		else
		{
			currentNode = nextNode;
			//std::cout << "Moved to adjacent node " << currentNode->get_value() << std::endl;
		}

	}while(!stk.empty());

	return traversalOrder;
}

/*
 * STRINGS
 */
template<typename Key>
std::string graph<Key>::node_list() const
{
	std::ostringstream stream;
	int currentNode = 0;

	stream << "[ ";
	for(auto nodePair : nodes)
	{
		stream << nodePair.second.key;
		if(currentNode < nodes.size() - 1)
		{
			stream << ", ";
		}
		currentNode++;
	}
	stream << " ]";

	return stream.str();
}

template<typename Key>
std::string graph<Key>::node_adjacency_list(const Key& key) const
{
	try {
		graph_node<Key>* node = at(key);
		std::ostringstream stream;
		int currentNode = 0;

		// Insert initial node into the stream
		stream << node->get_value() << " -> ";

		// Insert each adjacent node key into the stream
		for(auto nodePair : node->adjacencyList)
		{
			stream << nodePair.second->get_value();
			if(currentNode < node->adjacencyList.size() - 1)
			{
				stream << ", ";
			}
			currentNode++;
		}

		return stream.str();
	}
	catch(std::out_of_range& invArg) {
		return "";
	}
}

template<typename Key>
std::string graph<Key>::full_node_adjacency_list() const
{
	std::ostringstream stream;
	for(auto kvp : nodes)
	{
		stream << node_adjacency_list(kvp.first) << std::endl;
	}
	return stream.str();
}

template<typename Key>
std::string graph<Key>::node_mesh_list(const node_mesh& mesh)
{
	std::ostringstream stream;
	int currentNode;

	for(unsigned int i = 0; i < mesh.size(); i++)
	{
		currentNode = 0;
		stream << "Layer " << i << ": ";
		for(auto nodePair : mesh[i])
		{
			stream << nodePair.first;
			if(currentNode < mesh[i].size() - 1)
			{
				stream << ", ";
			}
			currentNode++;
		}
		stream << std::endl;
	}

	return stream.str();
}

/*
 * PRIVATE HELPERS
 */

template<typename Key>
int graph<Key>::enqueue_unvisited_adjacencies(const node* n, std::set<Key>& visited, std::queue<node*>& queue)
{
	int numEnqueued = 0;

	for(auto nodePair : n->adjacencyList)
	{
		if(visited.count(nodePair.first) == 0)
		{
			visited.insert(nodePair.first);
			queue.push(nodePair.second);
			numEnqueued++;
		}
	}

	return numEnqueued;
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
void graph<Key>::remove_adjacencies(const Key& removeKey)
{
	for(auto nodePair : nodes)
	{
		nodePair.second.adjacencyList.erase(removeKey);
	}
}

#endif /* GRAPH_H_ */
