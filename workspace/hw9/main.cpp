/*
 * main.cpp
 *
 *  Created on: May 13, 2019
 *      Author: chuntting0
 */

#include "graph_test_application.h"
using namespace std;

const std::string BREADTH_FIRST_TEST_FILE = "breadth.txt";
const std::string DEPTH_FIRST_TEST_FILE = "depth.txt";
const std::string KOSARAJU_TEST_FILE = "kosaraju.txt";
const std::string LARGE_TEST_FILE = "millions.txt";

int main()
{
	graph_test_application<int> app;
	app.setup_directed_graph_from_file(LARGE_TEST_FILE);

	cout << "Testing shortest distance algorithm" << endl;
	cout << "-----------------------------------" << endl;

	app.report_shortest_distance(1, 6);
	app.report_shortest_distance(5, 87);
	app.report_shortest_distance(4, 35);
	app.report_shortest_distance(43, 21);
	app.report_shortest_distance(3, 34);

	cout << endl;
	cout << "Testing strongly connected components algorithm" << endl;
	cout << "-----------------------------------------------" << endl;

	app.report_strongly_connected_components();

	return 0;
}
