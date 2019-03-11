#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <iostream>
#include <string>
#include <vector>
#include <functional>

template <typename Key, typename Value>
class binary_node
{
	// DATA
	private:
		Key key;
		Value value;
		// Parent of this node
		binary_node<Key, Value>* parent;
		// Left of this node
		binary_node<Key, Value>* left;
		// Right of this node
		binary_node<Key, Value>* right;	
	// MEHTODS
	public:
		binary_node<Key, Value>(Key k, Value v) 
			: key(k), value(v), parent(nullptr), left(nullptr), right(nullptr) {}
		binary_node<Key, Value>(Key k, Value v, binary_node<Key, Value>* p)
			: key(k), value(v), parent(p), left(nullptr), right(nullptr) {}
		void link_child(binary_node<Key, Value>*, bool left);
			// Link a child on the left or right as specified by boolean value
		void link_right(binary_node<Key, Value>*);
			// Connect a node to the right of this node by setting
			// this node's "right" pointer and the new node's "parent" pointer
		void link_left(binary_node<Key, Value>*);
			// Connect a node to the left of this node by setting
			// this node's "left" pointer and the new node's "parent" pointer
		binary_node<Key, Value>* sibling();
			// Return a pointer to a node that is a sibling to this node
			// == nullptr if:
			//		* this doesn't have a parent
			//		* this doesn't have a sibling
		binary_node<Key, Value>* child();
			// Return the left pointer, right pointer, or null pointer:
			//		* Returns left 
			//		* If left is null, returns right
			//		* If right is also null, return null
		bool root();
		bool internal();
		bool external();
		Value& operator*();
			// Dereference operator returns the value
	// FRIENDS
	template<typename, typename>
	friend class binary_tree;
		// Give binary tree access to all node's data
	friend class binary_tree_tester;
};

template <typename Key, typename Value>
class binary_tree
{
	// TYPES AND TYPEDEFS
	public:
		typedef binary_node<Key, Value> node;
		typedef binary_node<Key, Value>* iterator;
			// Tree's "iterator" is simply a binary node pointer
		typedef std::function<void(iterator&)> node_action;
			// Typedef for a functor that returns void 
			// and operates on a node iterator
	// DATA
	private:
		iterator root;
	// METHODS
	public:
		// CONSTRUCTORS
		binary_tree<Key, Value>() : root(nullptr) {}
		binary_tree<Key, Value>(Key k, Value v) : root(new node(k, v)) {} 
		void add(const Key&, const Value&);
		void add(const node&);
			// Add a node with the associated key-value pair
			// This method is guaranteed to add a node with the given
			// key-value pair with the key properly inserted
		void remove(const Key&);
			// Remove the node with the associated tree, maintaining
			// the ordered tree
		iterator find(const Key&) const;
			// Find a node with the given key. Return a pointer 
			// to the node found. Return null pointer if key was not found
		void clear();
			// Clear out all elements, and release all allocated space
		void print(std::ostream&);
			// Print out all elements in the tree in pre-order notation
		void preorder_traversal(const node_action&);
			// Perform pre-order traversal 
			// Call the function specified on each node visited
		void inorder_traversal(const node_action&);
			// Perform in-order traversal 
			// Call the function specified on each node visited
		void postorder_traversal(const node_action&);
			// Perform postorder traversal
			// Call the function specified on each node visited
		// DESTRUCTOR
		virtual ~binary_tree() { clear(); }
	// PROTECTED UTILITIES
	protected:
		iterator find_parent(const Key&) const;
			// Find the node that the given key should be
			// parented underneath. Return null if tree is empty
		iterator find_from(const Key&, iterator root) const;
			// Find and return an iterator with the given key,
			// starting at the given tree root
		void link_out(const iterator&);
			// Link the given iterator out of the tree by moving
			// one child up in the tree and making the other child
			// point to that child as the parent
		void preorder(iterator&, const node_action&);
		void inorder(iterator&, const node_action&);
		void postorder(iterator&, const node_action&);
	// FRIENDS
	friend class binary_tree_tester;
};

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

#endif // BINARY_TREE_H_
