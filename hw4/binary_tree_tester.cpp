#include "binary_tree.h"
using namespace std;

#include "binary_tree_tester.h"

/*
BINARY TREE TESTER IMPLEMENTATION
*/

void binary_tree_tester::testAdding()
{
	// Create a list of nodes to add
	vector<node> adding_nodes = {
		node(2, 'A'),
		node(3, 'C'),
		node(1, 'B')
	};
	cout << "Testing binary tree adding:" << endl;
	cout << "---------------------------" << endl;
	// Output each key-value of the nodes to add
	for(node n : adding_nodes)
	{
		cout << "Adding node [" << n.getKey() << ", " << n.getValue() << "]..." << endl;
		tree.add(n);
	}
	// Output the tree in preorder notation
	cout << "Current tree: ";
	tree.print(cout);
	cout << endl;
}
