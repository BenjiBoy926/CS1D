#ifndef BINARY_TREE_TESTER_H_
#define BINARY_TREE_TESTER_H_

#include "binary_node.h"
#include "binary_tree.h"

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
		void testAll();
		void testAdding();
		void testFinding();
};

#endif // BINARY_TREE_TESTER_H_