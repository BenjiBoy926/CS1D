#include "binary_tree.h"
#include "binary_tree_tester.h"
using namespace std;

/*
BINARY TREE TESTER IMPLEMENTATION
*/

void binary_tree_tester::test_all()
{
	test_adding();
	test_finding();
}

void binary_tree_tester::test_adding()
{
	// Create a list of nodes to add
	vector<node> adding_nodes = {
		node(4, 'A'),
		node(2, 'B'),
		node(3, 'E'),
		node(1, 'D'),
		node(2, 'B'),
		node(3, 'E'),
		node(4, 'A'),
		node(5, 'F'),
		node(6, 'C'),
		node(7, 'G'),
		node(1, 'D')
	};
	test_title("Testing binary tree adding");
	// Output each key-value of the nodes to add
	for(node n : adding_nodes)
	{
		cout << "Adding node [" << n.getKey() << ", " << n.getValue() << "]..." << endl;
		tree.add(n);
	}
	// Output the tree in preorder notation
	cout << "Current tree: ";
	tree.print(cout);
	cout << endl << endl;
}

void binary_tree_tester::test_finding()
{
	// Keys to find in the tree
	vector<int> keys = {
		4, 3, 7, 8, 0, 2
	};
	// HEADER
	test_title("Testing binary tree finding");
	output_current_state();
	cout << endl;
	// PROCESSING
	for(auto k : keys)
	{
		test_find_single(k);
		cout << endl;
	}
	cout << endl;
}

void binary_tree_tester::test_title(string title)
{
	cout << title << endl;
	// Output hyphens beneath the title
	cout << setfill('-');
	cout << setw(title.length()) << '-' << endl;
	cout << setfill(' ');
}

void binary_tree_tester::test_find_single(int key)
{
	node* target;
	cout << "Searching for key " << key << "..." << endl;
	target = tree.find(key);
	if(target != nullptr) 
	{
		cout << "Found node with data " << target->getValue() << endl;
	}
	else
	{
		cout << "No node found with key " << key << endl;
	}
}

void binary_tree_tester::output_current_state()
{
	// Output the current state of the tree
	cout << "Current tree: ";
	tree.print(cout);
	cout << endl;
}
