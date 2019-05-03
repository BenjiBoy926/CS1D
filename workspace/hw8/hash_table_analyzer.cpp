/*
 * hash_table_analyzer.cpp
 *
 *  Created on: May 1, 2019
 *      Author: chuntting0
 */

#include "hash_table_analyzer.h"
using namespace std;

vector<string> hash_table_analyzer::get_strings_from_file(const char* filename, int numElements)
{
	vector<string> strings;
	string tempString;
	ifstream fin;
	int index = 0;

	// Open the file
	fin.open(filename);

	// If file is open, extract number of elements desired,
	// or until end of file
	if(fin.is_open())
	{
		while(index < numElements && !fin.eof())
		{
			fin >> tempString;
			strings.push_back(tempString);
			index++;
		}

		// Close the file
		fin.close();
	}
	else
	{
		throw invalid_argument(string("For input string ") + filename + ": could not open file with name");
	}

	return strings;
}
