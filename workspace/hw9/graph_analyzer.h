/*
 * graph_analyzer.h
 *
 *  Created on: May 20, 2019
 *      Author: creat
 */

#ifndef GRAPH_ANALYZER_H_
#define GRAPH_ANALYZER_H_

#include <sstream>
#include "graph.h"

class graph_analyzer
{
// PUBLIC INTERFACE
public:
	template<typename Key>
	static std::string node_list(const graph<Key>&);

	template<typename Key>
	static std::string node_adjacency_listing(const graph<Key>&, const Key&);

	template<typename Key>
	static std::string full_node_adjacency_listing(const graph<Key>&);

	template<typename Key>
	static std::string node_mesh_listing(const typename graph<Key>::node_mesh& mesh);
};

template<typename Key>
std::string graph_analyzer::node_list(const graph<Key>& g)
{
	std::ostringstream stream;

	for(auto nodePair : g.nodes)
	{
		stream << nodePair.second.key << ", ";
	}

	return stream.str();
}

template<typename Key>
std::string graph_analyzer::node_adjacency_listing(const graph<Key>& g, const Key& key)
{
	try {
		graph_node<Key>* node = g.at(key);
		std::ostringstream stream;

		// Insert initial node into the stream
		stream << node->get_value() << " -> ";

		// Insert each adjacent node key into the stream
		for(auto nodePair : node->adjacencyList)
		{
			stream << nodePair.second->get_value() << ", ";
		}

		return stream.str();
	}
	catch(std::out_of_range& invArg) {
		return "";
	}
}

template<typename Key>
std::string graph_analyzer::full_node_adjacency_listing(const graph<Key>& g)
{
	std::ostringstream stream;

	for(auto kvp : g.nodes)
	{
		stream << node_adjacency_listing(g, kvp.first) << std::endl;
	}

	return stream.str();
}

template<typename Key>
std::string graph_analyzer::node_mesh_listing(const typename graph<Key>::node_mesh& mesh)
{
	std::ostringstream stream;

	for(unsigned int i = 0; i < mesh.size(); i++)
	{
		stream << "Layer " << i << ": ";
		for(auto nodePair : mesh[i])
		{
			stream << nodePair.first << ", ";
		}
		stream << std::endl;
	}

	return stream.str();
}

#endif /* GRAPH_ANALYZER_H_ */
