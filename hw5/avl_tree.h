#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include <vector>
#include <algorithm>
#include "binary_tree.h"

/*
 * CLASS avl_tree
 * --------------
 * A type of tree that re-balances itself on insertion, guaranteeing
 * O(logn) searching
 * --------------
 */

template<typename Key, typename Value>
class avl_tree : public binary_tree<Key, Value>
{
	// TYPES AND TYPEDEFS
	public:
		typedef binary_node<Key, Value> node;
		typedef binary_node<Key, Value>* iterator;
	// METHODS
	public:
		void add(const Key& k, const Value& v)
		{
			binary_tree<Key, Value>::add(k, v);
			// Check balance
			// Re-balance if unbalanced
		}
		void add(const node& n)
		{
			add(n.getKey(), n.getValue());
		}
		void remove(const Key& k)
		{
			// Must re-implement base method
		}
	// PROTECTED HELPERS
	protected:
		// Return true if the max difference in the depths of the leaves is at most 1
		bool is_avl() const
		{
			// Get a list of the leaves in the tree
			std::vector<iterator> nodes = leaves();
			// If the root is missing either subtree,
			// it should be included in the comparison
			if(this->root->left == nullptr || this->root->right == nullptr)
			{
				nodes.push_back(this->root);
			}
			// Create a function object that compares two iterators by their depth
			auto compare_by_depth = [](const iterator& itor1, const iterator& itor2) 
			{
				return itor1->depth() < itor2->depth();
			};
			// Sort nodes from least to greatest depth
			std::sort(nodes.begin(), nodes.end(), compare_by_depth);
			return (nodes.back()->depth - nodes.front()->depth) <= 1;
		}
		// Given the root, rotate the subtree to the right
		void rot_right(iterator& root)
		{
			// Store the root of the left subtree
			iterator leftSubtree = root->left;
			// Store the root of the subtree to rotate
			iterator parent = root->parent;
			// Have the root adopt the right subtree of the left child,
			// and have the left child adopt the root
			root->adopt_left(leftSubtree->right);
			leftSubtree->adopt_right(root);
			// If the root had a parent, we need to replace
			// it's child with the left subtree pointer
			if(root != nullptr)
			{
				bool rootIsLeft = parent->left == root;
				parent->adopt_child(leftSubtree, rootIsLeft);
			}
		}
		void rot_left(iterator& root)
		{
			// Store the root of the left subtree
			iterator rightSubtree = root->right;
			// Store the root of the subtree to rotate
			iterator parent = root->parent;
			// Have the root adopt the right child's left subtree,
			// and have the right child adopt the root
			root->adopt_right(rightSubtree->left);
			rightSubtree->adopt_left(root);
			// If the root had a parent, we need to replace
			// it's child with the left subtree pointer
			if(root != nullptr)
			{
				bool rootIsLeft = parent->left == root;
				parent->adopt_child(rightSubtree, rootIsLeft);
			}
		}
		void rot_right_left(iterator& root)
		{
			rot_right(root->right);
			rot_left(root);
		}
		void rot_left_right(iterator& root)
		{
			rot_left(root->left);
			rot_right(root);
		}
		// Return a vector with iterators to all of the leaves in the avl tree
		std::vector<iterator> leaves() const
		{
			std::vector<iterator> leaves_list;
			auto add_leaves = [&leaves_list](iterator& itor) 
			{
				// Push back the current iterator if it has no children 
				if(itor->external())
				{
					leaves_list.push_back(itor);
				}
			};
			// Traverse the whole tree, adding all leaves
			postorder_traversal(add_leaves);
			return leaves_list;
		}
};

#endif // AVL_TREE_H_
