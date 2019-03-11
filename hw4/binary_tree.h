#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include "binary_node.h"
#include <iostream>
#include <functional>

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
		// Add a node with the associated key-value pair
		// This method is guaranteed to add a node with the given
		// key-value pair with the key properly inserted
		void add(const Key& k, const Value& v)
		{
			// Find the parent that the new node belongs to
			iterator parent = find_parent(k);
			// If no parent is found, we know this node is the root
			if(parent == nullptr)
			{
				root = new node(k, v);
			}
			// If key to add is bigger than parent key...
			else if(k > parent->key)
			{
				//...link up new node on the right of the parent
				parent->link_right(new node(k, v));
			}
			// If key to add is smaller than parent key...
			else
			{
				//...link up new node on the left of the parent
				parent->link_left(new node(k, v));
			}
		}
		void add(const node& n)
		{
			add(n.key, n.value);
		}
		// Remove the node with the associated tree, maintaining
		// the ordered tree
		void remove(const Key& k)
		{
			// Find the node to remove
			iterator rm = find(k);
			// Link the node out of the tree,
			// and deallocate its data
			if(rm != nullptr)
			{
				link_out(rm);
				delete rm;
			}
		}
		// Find a node with the given key. Return a pointer 
		// to the node found. Return null pointer if key was not found
		iterator find(const Key& k) const
		{
			return find_from(k, root);
		}
		// Clear out all elements, and release all allocated space
		void clear()
		{
			// Perform a postorder traversal, deleting every node on the each visit
			auto delete_node = [](const iterator& itor) {
				delete itor;
			};
			postorder_traversal(delete_node);
		}
		// Print out all elements in the tree in pre-order notation
		void print(std::ostream& out)
		{
			// Perform a preorder traversal, printing the value of the node on each visit
			auto print_node = [&out](const iterator& itor) { 
				out << itor->value << ' ';
			};
			preorder_traversal(print_node);
		}
		// Perform pre-order traversal 
		// Call the function specified on each node visited
		void preorder_traversal(const node_action& action)
		{
			preorder(root, action);
		}
		// Perform in-order traversal 
		// Call the function specified on each node visited
		void inorder_traversal(const node_action& action)
		{
			inorder(root, action);
		}
		// Perform postorder traversal
		// Call the function specified on each node visited
		void postorder_traversal(const node_action& action)
		{
			postorder(root, action);
		}
		// DESTRUCTOR
		virtual ~binary_tree() 
		{ 
			clear(); 
		}
	// PROTECTED UTILITIES
	protected:
		// Find the node that the given key should be
		// parented underneath. Return null if tree is empty
		iterator find_parent(const Key& key) const
		{
			// Start an iterator at the root node
			iterator current = root;
			iterator previous = nullptr;
			// Loop until current is null
			while(current != nullptr)
			{
				previous = current;
				// If key searched for is smaller than current key...
				if(key < current->key)
				{
					//...move to the left
					current = current->left;
				}
				// If key searched for is bigger than current key...
				else
				{
					//...move to the right
					current = current->right;
				}
			}
			// Return the parent of the null place where the key belongs
			return previous;
		}
		// Find and return an iterator with the given key,
		// starting at the given tree root
		iterator find_from(const Key& k, iterator root) const
		{
			// Pre-check if root is null
			if(root == nullptr)
			{
				return nullptr;
			}
			// If key is less than root key,
			// search in left subtree
			if(k < root->key)
			{
				return find_from(k, root->left);
			}
			// If key is bigger than root key,
			// search in right subtree
			else if(k > root->key)
			{
				return find_from(k, root->right);
			}
			// If keys are equal, return the root
			else
			{
				return root;
			}
		}
		// Link the given iterator out of the tree by moving
		// one child up in the tree and making the other child
		// point to that child as the parent
		void link_out(const iterator& rm)
		{
			// Grab all adjacent nodes
			iterator left = rm->left;
			iterator right = rm->right;
			iterator parent = rm->parent;

			if(parent != nullptr)
			{
				// Check to see if this is the left child of the parent
				bool isLeftChild = parent->left == rm;
				// Link the child of the node on the same side of the parent
				// node that this node is on
				if(left != nullptr)
				{
					parent->link_child(left, isLeftChild);
				}
				else if(right != nullptr)
				{
					parent->link_child(right, isLeftChild);
				}
			}
			// If iterator to remove has both children...
			if(left != nullptr && right != nullptr)
			{
				//...parent the right child beneath the left one
				left->link_right(right);
			}
		}
		void preorder(iterator& root, const node_action& action)
		{
			// Perform the action on the root
			action(root);
			// If a left subtree exists, apply preorder to it
			if(root->left != nullptr)
			{
				preorder(root->left, action);
			}
			// If a right subtree exists, apply preorder to it
			if(root->right != nullptr)
			{
				preorder(root->right, action);
			}
		}
		void inorder(iterator& root, const node_action& action)
		{
			// Traverse the left subtree
			if(root->left != nullptr)
			{
				inorder(root->left, action);
			}
			// Perform the action after traversing the left subtree
			action(root);
			// Traverse the right subtree
			if(root->right != nullptr)
			{
				inorder(root->right, action);
			}
		}
		void postorder(iterator& root, const node_action& action)
		{
			// If a left subtree exists, traverse it
			if(root->left != nullptr)
			{
				postorder(root->left, action);
			}
			// If a right subtree exists, travers it
			if(root->right != nullptr)
			{
				postorder(root->right, action);
			}
			// Perform the action last
			action(root);
		}
};

#endif // BINARY_TREE_H_
