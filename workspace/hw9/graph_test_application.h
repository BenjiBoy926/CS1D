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

const std::string BREADTH_FIRST_TEST_FILE = "breadth.txt";
const std::string DEPTH_FIRST_TEST_FILE = "depth.txt";
const std::string KOSARAJU_TEST_FILE = "kosaraju.txt";

class graph_test_application
{
// PRIVATE DATA
private:
	// Privatize constructor to prevent construction
	graph_test_application();

	// Graph to test
	static graph<int> graph;

// PUBLIC INTERFACE
public:
	static void report_depth_first_traversal();
	static void report_breadth_first_traversal();

// PRIVATE HELPERS
private:
	static void build_depth_first_test_graph();
	static void build_breadth_first_test_graph();
};

#endif /* GRAPH_TEST_APPLICATION_H_ */
