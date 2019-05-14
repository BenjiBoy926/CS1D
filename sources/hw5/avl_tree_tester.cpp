#include "avl_tree_tester.h"
using namespace std;

void avl_tree_tester::test_adding()
{
	//const int ASCII_OFFSET = 64;
	vector<node> nodesToAdd = {
			node(10, 10),
			node(6, 6),
			node(2, 2),
			node(1, 1),
			node(3, 3),
			node(5, 5),
			node(9, 9),
			node(8, 8),
			node(7, 7),
			node(4, 4),
			node(11, 11)
	};
	this->test_title("Testing avl tree adding");
	// Output each key-value of the nodes to add
	for(node n : nodesToAdd)
	{
		cout << "Adding node [" << n.get_key() << ", " << n.get_value() << "]..." << endl;
		tree.add(n);
		this->output_current_state();
	}
}

void avl_tree_tester::output_current_state() const
{
	cout << "Current tree state: ";
	this->tree.print(cout);
	cout << endl;
}

void avl_tree_tester::test_title(const string& title)
{
	cout << title << endl;
	// Output hyphens beneath the title
	cout << setfill('-');
	cout << setw(title.length()) << '-' << endl;
	cout << setfill(' ');
}
