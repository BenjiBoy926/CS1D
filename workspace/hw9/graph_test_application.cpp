/*
 * graph_test_application.cpp
 *
 *  Created on: May 13, 2019
 *      Author: chuntting0
 */

#include "graph_test_application.h"
using namespace std;

graph<int> graph_test_application::graph;

void graph_test_application::report_depth_first_traversal()
{
	build_depth_first_test_graph();
	auto depthFirstPath = graph.depth_first_traversal(0);

	cout << "Depth first traversal path:" << endl;
	cout << "---------------------------" << endl;
	for(unsigned int i = 0; i < depthFirstPath.size(); i++)
	{
		cout << depthFirstPath[i].get_key() << ", ";
	}
	cout << endl << endl;
}

void graph_test_application::report_breadth_first_traversal()
{
	build_breadth_first_test_graph();
	auto breadthFirstPath = graph.breadth_first_traversal(0);

	cout << "Breadth first traversal path:" << endl;
	cout << "-----------------------------" << endl;
	for(unsigned int i = 0; i < breadthFirstPath.size(); i++)
	{
		cout << breadthFirstPath[i].get_key() << ", ";
	}
	cout << endl << endl;
}

void graph_test_application::build_depth_first_test_graph()
{
	graph.clear();
	graph_builder::add_undirected_edges_from_file(graph, DEPTH_FIRST_TEST_FILE);
}

void graph_test_application::build_breadth_first_test_graph()
{
	graph.clear();
	graph_builder::add_undirected_edges_from_file(graph, BREADTH_FIRST_TEST_FILE);
}
