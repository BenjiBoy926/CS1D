#include "binary_tree.h"
using namespace std;

/*
BINARY NODE IMPLEMENTATION
*/

template <typename Key, typename Value>
void binary_node<Key, Value>::link_child(binary_node<Key, Value>* new_node, bool left)
{
	if(left)
	{
		link_left(new_node);
	}
	else
	{
		link_right(new_node);
	}
}

template <typename Key, typename Value>
void binary_node<Key, Value>::link_right(binary_node<Key, Value>* new_node)
{
	new_node->parent = this;
	right = new_node;
}

template <typename Key, typename Value>
void binary_node<Key, Value>::link_left(binary_node<Key, Value>* new_node)
{
	new_node->parent = this;
	left = new_node;
}

template <typename Key, typename Value>
binary_node<Key, Value>* binary_node<Key, Value>::sibling()
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

template <typename Key, typename Value>
binary_node<Key, Value>* binary_node<Key, Value>::child()
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

template <typename Key, typename Value>
bool binary_node<Key, Value>::root()
{
	return parent == nullptr;
}

template <typename Key, typename Value>
bool binary_node<Key, Value>::internal()
{
	return left != nullptr || right != nullptr;
}

template <typename Key, typename Value>
bool binary_node<Key, Value>::external()
{
	return !internal();
}

template <typename Key, typename Value>
Value& binary_node<Key, Value>::operator*()
{
	return value;
}

/*
BINARY TREE IMPLEMENTATION
*/

template <typename Key, typename Value>
void binary_tree<Key, Value>::add(const Key& k, const Value& v)
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

template <typename Key, typename Value>
void binary_tree<Key, Value>::add(const node& new_node)
{
	add(new_node.key, new_node.value);
}

template <typename Key, typename Value>
void binary_tree<Key, Value>::remove(const Key& k)
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

template <typename Key, typename Value>
binary_tree<Key, Value>::iterator 
binary_tree<Key, Value>::find(const Key& k) const
{
	return find_from(k, root);
}

template <typename Key, typename Value>
void binary_tree<Key, Value>::clear()
{
	clear_from(root);
}

template <typename Key, typename Value>
binary_tree<Key, Value>::iterator 
binary_tree<Key, Value>::find_parent(const Key& key) const
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

template <typename Key, typename Value>
binary_tree<Key, Value>::iterator 
binary_tree<Key, Value>::find_from(const Key& k, iterator root) const
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

template <typename Key, typename Value>
void binary_tree<Key, Value>::link_out(const iterator& rm)
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

template <typename Key, typename Value>
void binary_tree<Key, Value>::clear_from(iterator& root, iterator& parent)
{
	// If the root exists, clear out its subtrees
	if(root != nullptr)
	{
		// Clear out the left subtree
		clear_from(root->left, root);
		// Clear out the right subtree
		clear_from(root->right, root);
	}
	else
	{

	}
}

template <typename Key, typename Value>
void binary_tree<Key, Value>::preorder_traversal(const node_action& action)
{
	preorder(root, action);
}

template <typename Key, typename Value>
void binary_tree<Key, Value>::postorder_traversal(const node_action& action)
{
	postorder(root, action);
}

template <typename Key, typename Value>
void binary_tree<Key, Value>::preorder(iterator& root, const node_action& action)
{
	// Perform the action on the root
	action(root);
	// If a left subtree exists, apply preorder to it
	if(root->left != nullptr)
	{
		preorder(root->left);
	}
	// If a right subtree exists, apply preorder to it
	if(root->right != nullptr)
	{
		preorder(root->right);
	}
}

template <typename Key, typename Value>
void binary_tree<Key, Value>::postorder(iterator& root, const node_action& action)
{
	// If a left subtree exists, traverse it
	if(root->left != nullptr)
	{
		postorder(root->left);
	}
	// If a right subtree exists, travers it
	if(root->right != nullptr)
	{
		postorder(root->right);
	}
	// Perform the action last
	action(root);
}

/*
BINARY TREE TESTER IMPLEMENTATION
*/
