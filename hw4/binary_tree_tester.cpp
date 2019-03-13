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
	test_removal();
	test_clear();
}

void binary_tree_tester::test_adding()
{
	// Create a list of nodes to add
	vector<node> adding_nodes = {
		node(8, 'A'),
		node(4, 'B'),
		node(10, 'C'),
		node(2, 'D'),
		node(6, 'E'),
		node(9, 'J'),
		node(11, 'K'),
		node(1, 'F'),
		node(3, 'G'),
		node(5, 'H'),
		node(7, 'I')
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

void binary_tree_tester::test_removal()
{
	// List of keys to remove from the list
	vector<int> rm_keys = {
		0, 12, 9, 10, 2, 4, 8
	};
	// Output the title and current tree 
	test_title("Testing binary tree removal");
	output_current_state();
	cout << endl;
	// Remove the nodes at each of the keys
	for(int key : rm_keys)
	{
		test_remove_single(key);
		output_current_state();
		cout << endl;
	}
}

void binary_tree_tester::test_clear()
{
	test_title("Testing binary tree clear");
	output_current_state();
	cout << "Clearing the tree..." << endl;
	output_current_state();
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

void binary_tree_tester::test_remove_single(int key)
{
	cout << "Removing node with key " << key << "..." << endl;
	tree.remove(key);
}

void binary_tree_tester::output_current_state()
{
	// Output the current state of the tree
	cout << "Current tree: ";
	tree.print(cout);
	cout << endl;
}
