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
			// If the addition unbalanced the tree, rebalance it
			if(!is_avl())
			{
				this->rebalance(k);
			}
		}
		void add(const node& n)
		{
			add(n.get_key(), n.get_value());
		}
		void remove(const Key& k)
		{
			// Must re-implement base method
		}
	// PROTECTED HELPERS
	protected:
		// Return true if the whole tree is balanced
		bool is_avl() const
		{
			return this->is_avl(this->root);
		}
		// Return true if the tree represented by the given root is balanced
		bool is_avl(const iterator& subtreeRoot) const
		{
			// If null is passed in, return true
			if(subtreeRoot == nullptr)
			{
				return true;
			}
			/*
			 * The tree has avl properties if:
			 * -------------------------------
			 * (1) The balance of the tree is <= 1
			 * (2) The balance of the left subtree is <= 1
			 * (3) The balance of the right subtree is <= 1
			 * -------------------------------
			 */
			else
			{
				bool rightIsAvl = this->is_avl(subtreeRoot->get_right());
				bool leftIsAvl = this->is_avl(subtreeRoot->get_left());
				return std::abs(subtreeRoot->balance()) <= 1 && rightIsAvl && leftIsAvl;
			}
		}
		// Re-balance the tree given the key of the node that is
		// throwing the tree off balance
		void rebalance(const Key& offenderKey)
		{
			// Find the offender, then find the first node above the offender
			// that is the root of an unbalanced tree
			iterator offender = this->find(offenderKey);
			iterator rebalanceRoot = this->find_first_not_balanced(offender);
			// True if the offender is in the left child of it's parent
			bool leftChild = offender->get_key() < rebalanceRoot->get_key();
			// True if the offender is in the left subtree of the child beneath the root
			bool leftSubtree;
			// Check the offender's tree with the right or left child of the root,
			// depending on whose child the offender is
			if(leftChild)
			{
				leftSubtree = offender->get_key() < rebalanceRoot->get_left()->get_key();
			}
			else
			{
				leftSubtree = offender->get_key() < rebalanceRoot->get_right()->get_key();
			}
			// Perform rotation depending on where the out of balance
			// node is relative to the rebalance
			if(leftChild && leftSubtree)
			{
				rot_right(rebalanceRoot);
			}
			else if(!leftChild && leftSubtree)
			{
				rot_right_left(rebalanceRoot);
			}
			else if(leftChild && !leftSubtree)
			{
				rot_left_right(rebalanceRoot);
			}
			else
			{
				rot_left(rebalanceRoot);
			}
		}
		// Given the root, rotate the subtree to the right
		void rot_right(iterator subtreeRoot)
		{
			/*
			 * PRECHECKS
			 * ---------
			 * Grab some info about the subtree we're about to rotate
			 * before messing with the pointers
			 * ---------
			 */

			// Store if the root we're rotating is the tree's overall root
			bool rotatingRoot = subtreeRoot == this->root;
			// Store the parent of the subtree to rotate, if any
			iterator parent = subtreeRoot->get_parent();
			bool subtreeRootIsLeft;
			// Determine which child the subtree root is before moving the tree around
			if(parent != nullptr)
			{
				subtreeRootIsLeft = parent->get_left() == subtreeRoot;
			}

			/*
			 * BODY
			 * ----
			 * Perform the actual rotation
			 * ----
			 */

			// Store the root of the left subtree
			iterator leftSubtree = subtreeRoot->get_left();
			// Have the root adopt the right subtree of the left child,
			// and have the left child adopt the root
			subtreeRoot->adopt_left(leftSubtree->get_right());
			leftSubtree->adopt_right(subtreeRoot);

			/*
			 * POSTCHECKS
			 * ----------
			 * Use info stored from the pre-check to repair
			 * any problems created by the rotation
			 * ----------
			 */

			// If the root had a parent, we need to replace
			// it's child with the left subtree pointer
			if(parent != nullptr)
			{
				parent->adopt_child(leftSubtree, subtreeRootIsLeft);
			}
			// If the subtreeRoot is the root of the entire tree,
			// update the root to point to the left subtree that rotated into its place
			if(rotatingRoot)
			{
				this->root = leftSubtree;
			}
		}
		void rot_left(iterator subtreeRoot)
		{
			/*
			 * PRECHECKS
			 * ---------
			 * Grab some info about the subtree we're about to rotate
			 * before messing with the pointers
			 * ---------
			 */

			// Determine if we are rotating the root of the whole tree
			bool rotatingRoot = subtreeRoot == this->root;
			// Store the parent of the subtree to rotate, if any
			iterator parent = subtreeRoot->get_parent();
			bool subtreeRootIsLeft;
			// Determine which child the subtree root is before moving the tree around
			if(parent != nullptr)
			{
				subtreeRootIsLeft = parent->get_left() == subtreeRoot;
			}

			/*
			 * BODY
			 * ----
			 * Perform the actual rotation
			 * ----
			 */

			// Store the root of the left subtree
			iterator rightSubtree = subtreeRoot->get_right();
			// Have the root adopt the right child's left subtree,
			// and have the right child adopt the root
			subtreeRoot->adopt_right(rightSubtree->get_left());
			rightSubtree->adopt_left(subtreeRoot);

			/*
			 * POSTCHECKS
			 * ----------
			 * Use info stored from the pre-check to repair
			 * any problems created by the rotation
			 * ----------
			 */

			// If the root had a parent, we need to replace
			// it's child with the left subtree pointer
			if(parent != nullptr)
			{
				parent->adopt_child(rightSubtree, subtreeRootIsLeft);
			}
			// If we rotated the root of the entire tree,
			// replace the root with the right subtree that rotated into its place
			if(rotatingRoot)
			{
				this->root = rightSubtree;
			}
		}
		void rot_right_left(iterator subtreeRoot)
		{
			rot_right(subtreeRoot->get_right());
			rot_left(subtreeRoot);
		}
		void rot_left_right(iterator subtreeRoot)
		{
			rot_left(subtreeRoot->get_left());
			rot_right(subtreeRoot);
		}
		// Given an iterator, find the first iterator above it
		// in the heirarchy whose tree is unbalanced
		iterator find_first_not_balanced(const iterator& itor)
		{
			// If this iterator's tree is avl, check the one above it
			if(std::abs(itor->balance()) <= 1 && itor->get_parent() != nullptr)
			{
				return this->find_first_not_balanced(itor->get_parent());
			}
			else
			{
				return itor;
			}
		}
};

#endif // AVL_TREE_H_
