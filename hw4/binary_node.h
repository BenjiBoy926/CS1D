#ifndef BINARY_NODE_H_
#define BINARY_NODE_H_

#include "binary_tree.h"

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
		
		// GETTERS
		Key getKey() { return key; }
		Value getValue() { return value; }

		// Link a child on the left or right as specified by boolean value
		void link_child(binary_node<Key, Value>* child, bool left)
		{
			if(left)
			{
				link_left(child);
			}
			else
			{
				link_right(child);
			}
		}

		// Connect a node to the right of this node by setting
		// this node's "right" pointer and the new node's "parent" pointer
		void link_right(binary_node<Key, Value>* child)
		{
			child->parent = this;
			right = child;
		}

		// Connect a node to the left of this node by setting
		// this node's "left" pointer and the new node's "parent" pointer	
		void link_left(binary_node<Key, Value>*)
		{
			child->parent = this;
			left = child;
		}

		// Return a pointer to a node that is a sibling to this node
		// == nullptr if:
		//		* this doesn't have a parent
		//		* this doesn't have a sibling
		binary_node<Key, Value>* sibling()
		{
			if(parent != nullptr)
			{
				// If this is the left node, return the right node
				if(parent->left = this)
				{
					return parent->right;
				}
				// If this is the right node, return the left node
				else
				{
					return parent->left;
				}	
			}
			// If this has no parent, return null
			else
			{
				return nullptr;
			}
		}

		// Return the left pointer, right pointer, or null pointer:
		//		* Returns left 
		//		* If left is null, returns right
		//		* If right is also null, return null
		binary_node<Key, Value>* child()
		{
			if(left != nullptr)
			{
				return left;
			}
			else 
			{
				// (Right is guaranteed to be null if not initialized,
				// so the function contract is still fulfilled)
				return right;
			}
		}

		bool root()
		{
			return parent == nullptr;
		}
		bool internal()
		{
			return left != nullptr || right != nullptr;
		}
		bool external()
		{
			return !internal();
		}

		// Dereference operator returns the value
		Value& operator*()
		{
			return value;
		}
	// FRIENDS
	template<typename, typename>
	friend class binary_tree;
};

#endif // BINARY_NODE_H_