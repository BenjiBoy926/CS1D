#ifndef AVL_TREE_H_
#define AVL_TREE_H_

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
		typedef binary_tree<Key, Value> binary_tree;
	// METHODS
	public:
		void add(const Key& k, const Value& v)
		{
			binary_tree::add(k, v);
			// Check balance
			// Re-balance if unbalanced
		}
		void add(const node& n)
		{
			add(n.key, n.value);
		}
		void remove(const Key& k)
		{
			// Must re-implement base method
		}
	// PROTECTED HELPERS
	protected:
		// Return the height of the node
		// represented by the given iterator
		int height(const iterator& root);
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
};

#endif // AVL_TREE_H_
