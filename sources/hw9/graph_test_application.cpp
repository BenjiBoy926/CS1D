/*
 * graph_test_application.cpp
 *
 *  Created on: May 13, 2019
 *      Author: chuntting0
 */

#include "graph_test_application.h"

graph<int, int> graph_test_application::graph;

void graph_test_application::report_depth_first_traversal()
{
	build_depth_first_test_graph();
	auto depthFirstPath = graph.depth_first_traversal(0);

	for(unsigned int i = 0; i < depthFirstPath.size(); i++)
	{
		std::cout << depthFirstPath[i].get_key() << ", ";
	}
}

void graph_test_application::build_depth_first_test_graph()
{
	graph.clear();

	graph.add(0, 0);
	graph.add(1, 0);
	graph.add(2, 0);
	graph.add(3, 0);
	graph.add(4, 0);
	graph.add(5, 0);
	graph.add(6, 0);

	graph.add_undirected_edge(0, 1);
	graph.add_undirected_edge(0, 2);
	graph.add_undirected_edge(0, 4);

	graph.add_undirected_edge(1, 3);
	graph.add_undirected_edge(1, 4);

	graph.add_undirected_edge(3, 4);

	graph.add_undirected_edge(2, 5);
	graph.add_undirected_edge(2, 6);

	graph.add_undirected_edge(6, 5);
}
