#ifndef BINARY_TREE_TESTER_H_
#define BINARY_TREE_TESTER_H_

#include "binary_tree.h"
#include <vector>
#include <string>
#include <iomanip>

// Helper class used to test the binary tree class
class binary_tree_tester
{
	// TYPES AND TYPEDEFS
	public:
		typedef binary_node<int, char> node;
	// DATA
	private:
		// Binary tree to be tested
		binary_tree<int, char> tree;
	// METHODS
	public:
		binary_tree_tester() : tree(binary_tree<int, char>()) {}
		void test_all();
		void test_adding();
		void test_finding();
		// Output the tree
		void output_current_state();
	// PROTECTED UTILITIES
	protected:
		// Output title of the string
		void test_title(std::string);
		// Try to find a single key and output the results
		void test_find_single(int key);
		// Try to find a single key, remove it, and output the results
		void test_remove_single(int key);
};

#endif // BINARY_TREE_TESTER_H_
