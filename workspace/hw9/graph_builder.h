/*
 * graph_builder.h
 *
 *  Created on: May 13, 2019
 *      Author: chuntting0
 */

#ifndef GRAPH_BUILDER_H_
#define GRAPH_BUILDER_H_

#include <functional>
#include <fstream>
#include "graph.h"
#include "graph_analyzer.h"

class graph_builder
{
// PUBLIC INTERFACE
public:
	template<typename Key>
	static void add_directed_edges_from_file(graph<Key>&, const std::string&);

	template<typename Key>
	static void add_undirected_edges_from_file(graph<Key>&, const std::string&);
};

template<typename Key>
void graph_builder::add_directed_edges_from_file(graph<Key>& g, const std::string& filename)
{
	std::ifstream fin;
	Key parentKey;
	Key childKey;

	fin.open(filename);

	if(fin.is_open())
	{
		while(!fin.eof())
		{
			fin >> parentKey >> childKey;

			// Make sure extraction didn't fail before adding the edge
			if(!fin.fail())
			{
				g.add_directed_edge(parentKey, childKey);
			}
		}

		fin.close();
	}
}

template<typename Key>
void graph_builder::add_undirected_edges_from_file(graph<Key>& g, const std::string& filename)
{
	std::ifstream fin;
	Key parentKey;
	Key childKey;

	fin.open(filename);

	if(fin.is_open())
	{
		while(!fin.eof())
		{
			fin >> parentKey >> childKey;

			// Make sure extraction didn't fail before adding the edge
			if(!fin.fail())
			{
				g.add_undirected_edge(parentKey, childKey);
			}
		}

		fin.close();
	}
}

#endif /* GRAPH_BUILDER_H_ */
