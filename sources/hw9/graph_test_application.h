/*
 * graph_test_application.h
 *
 *  Created on: May 13, 2019
 *      Author: chuntting0
 */

#ifndef GRAPH_TEST_APPLICATION_H_
#define GRAPH_TEST_APPLICATION_H_

#include <iostream>
#include "graph.h"

class graph_test_application
{
// PRIVATE DATA
private:
	// Privatize constructor to prevent construction
	graph_test_application();

	// Graph to test
	static graph<int, int> graph;

// PUBLIC INTERFACE
public:
	static void report_depth_first_traversal();

// PRIVATE HELPERS
private:
	static void build_depth_first_test_graph();
};

#endif /* GRAPH_TEST_APPLICATION_H_ */
