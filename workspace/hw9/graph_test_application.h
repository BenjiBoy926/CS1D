/*
 * graph_test_application.h
 *
 *  Created on: May 13, 2019
 *      Author: chuntting0
 */

#ifndef GRAPH_TEST_APPLICATION_H_
#define GRAPH_TEST_APPLICATION_H_

#include <iostream>
#include "graph_analyzer.h"
#include "graph_builder.h"

template<typename Key>
class graph_test_application
{
// PRIVATE DATA
private:
	// Graph to test
	graph<Key> testGraph;

// PUBLIC INTERFACE
public:
	// Construct the application's graph with the given filename
	// as if by calling "setup_graph_from_file"
	graph_test_application() : testGraph() {};

	graph<Key> get_graph() const { return testGraph; }

	// Report shortest distance between two nodes
	void report_shortest_distance(const Key& begin, const Key& end) const;

	// Report the resulting stack of a depth-first traversal
	void report_depth_first_traversal(const Key& begin) const;

	// Report all strongly connected components in the graph
	void report_strongly_connected_components() const;

	// Setup graph from file with the given name
	void setup_directed_graph_from_file(const std::string& filename);
	void setup_undirected_graph_from_file(const std::string& filename);
};

template<typename Key>
void graph_test_application<Key>::report_shortest_distance(const Key& begin, const Key& end) const
{
	try {
		int distance = testGraph.distance(begin, end);

		// Report the distance obtained
		if(distance >= 0)
		{
			std::cout << "The distance between " << begin << " and " << end << " is " << distance << std::endl;
		}
		else
		{
			std::cout << "No path exists between " << begin << " and " << end << std::endl;
		}
	}
	catch(std::out_of_range& error) {
		std::cout << "Either " << begin << " or " << end << " is not in the graph" << std::endl;
	}
}

template<typename Key>
void graph_test_application<Key>::report_depth_first_traversal(const Key& begin) const
{
	std::cout << "Depth first traversal stack" << std::endl;
	std::cout << "---------------------------" << std::endl;

	auto list = testGraph.depth_first_traversal(begin);

	for(auto n : list)
	{
		std::cout << n.get_value() << ", ";
	}
}

template<typename Key>
void graph_test_application<Key>::report_strongly_connected_components() const
{
	auto mesh = testGraph.strongly_connected_components();
	std::cout << graph_analyzer::node_mesh_listing<Key>(mesh);
}

template<typename Key>
void graph_test_application<Key>::setup_directed_graph_from_file(const std::string& filename)
{
	testGraph.clear();
	graph_builder::add_directed_edges_from_file(testGraph, filename);
}

template<typename Key>
void graph_test_application<Key>::setup_undirected_graph_from_file(const std::string& filename)
{
	testGraph.clear();
	graph_builder::add_undirected_edges_from_file(testGraph, filename);
}

#endif /* GRAPH_TEST_APPLICATION_H_ */
