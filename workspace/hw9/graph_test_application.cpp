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
	std::cout << std::endl;
}

void graph_test_application::report_breadth_first_traversal()
{
	build_breadth_first_test_graph();
	auto breadthFirstPath = graph.breadth_first_traversal(0);

	for(unsigned int i = 0; i < breadthFirstPath.size(); i++)
	{
		std::cout << breadthFirstPath[i].get_key() << ", ";
	}
	std::cout << std::endl;
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

void graph_test_application::build_breadth_first_test_graph()
{
	graph.clear();

	graph.add(0, 0);
	graph.add(1, 0);
	graph.add(2, 0);
	graph.add(3, 0);
	graph.add(4, 0);
	graph.add(5, 0);
	graph.add(6, 0);
	graph.add(7, 0);
	graph.add(8, 0);
	graph.add(9, 0);

	graph.add_undirected_edge(0, 1);
	graph.add_undirected_edge(0, 3);

	graph.add_undirected_edge(1, 2);
	graph.add_undirected_edge(1, 4);
	graph.add_undirected_edge(1, 6);
	graph.add_undirected_edge(1, 7);

	graph.add_undirected_edge(2, 3);
	graph.add_undirected_edge(2, 8);
	graph.add_undirected_edge(2, 9);

	graph.add_undirected_edge(4, 6);
	graph.add_undirected_edge(4, 7);
	graph.add_undirected_edge(4, 5);

	graph.add_undirected_edge(6, 7);
}
