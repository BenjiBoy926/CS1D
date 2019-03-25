#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <iostream>
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
		
		// GETTERS
		Key getKey() { return key; }
		Value getValue() { return value; }

		// Link a child on the left or right as specified by boolean value
		void adopt_child(binary_node<Key, Value>* child, bool left)
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
		void adopt_right(binary_node<Key, Value>* child)
		{
			child->parent = this;
			right = child;
		}
		// Connect a node to the left of this node by setting
		// this node's "left" pointer and the new node's "parent" pointer	
		void adopt_left(binary_node<Key, Value>* child)
		{
			child->parent = this;
			left = child;
		}
		// Ground the left or right child depending on boolean value
		void abandon_child(bool left)
		{
			if(left)
			{
				abandon_left();
			}
			else
			{
				abandon_right();
			}	
		}
		// Ground both children
		void abandon_children()
		{
			abandon_left();
			abandon_right();
		}
		// Ground the right child by making it null, and making it's parent null
		void abandon_right()
		{
			if(right != nullptr)
			{
				right->parent = nullptr;
				right = nullptr;
			}
		}
		// Ground the left child by making it null, and making it's parent null
		void abandon_left()
		{
			if(left != nullptr)
			{
				left->parent = nullptr;
				left = nullptr;
			}
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
				if(parent->left == this)
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
		// Return the node all the way down on the tree, furthest to the right
		binary_node<Key, Value>* rightmost_descendent()
		{
			if(right != nullptr)
			{
				return right->rightmost_descendent();
			}
			else if(left != nullptr)
			{
				return left->rightmost_descendent();
			}
			else
			{
				return this;
			}
		}
		// Return the depth of this node in the tree
		int depth()
		{
			if(parent != nullptr)
			{
				return 1 + parent->depth();
			}
			else
			{
				return 0;
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
	// Give binary tree class access to private members
	template<typename, typename>
	friend class binary_tree;	
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
		// Add a node with the associated key-value pair
		// This method is guaranteed to add a node with the given
		// key-value pair with the key properly inserted
		virtual void add(const Key& k, const Value& v)
		{
			if(root == nullptr)
			{
				root = new node(k, v);
			}
			else
			{
				// Find the parent that the new node belongs to
				iterator parent = find_parent(k);
				// If no parent is found, we know this node is the root
				if(parent != nullptr)
				{
					// If key to add is bigger than parent key...
					if(k > parent->key)
					{
						//...link up new node on the right of the parent
						parent->adopt_right(new node(k, v));
					}
					// If key to add is smaller than parent key...
					else
					{
						//...link up new node on the left of the parent
						parent->adopt_left(new node(k, v));
					}
				}
			}
		}
		virtual void add(const node& n)
		{
			add(n.key, n.value);
		}
		// Remove the node with the associated tree, maintaining
		// the ordered tree
		virtual void remove(const Key& k)
		{
			// Find the node to remove
			iterator rm = find(k);
			// Link the node out of the tree,
			// and deallocate its data
			if(rm != nullptr)
			{
				link_out(rm);
				// If we just removed the root, replace it
				if(rm == root)
				{
					// If the node has a left child...
					if(rm->left != nullptr)
					{
						//...replace the root with the left child
						root = rm->left;
					}
					// If the node has no left child and a right child...
					else if(rm->right != nullptr)
					{
						//...replace the root with right child
						root = rm->right;
					}
					// If the node has no children...
					else
					{
						//...replace the root with null
						root = nullptr;
					}
				}
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
			// Perform a postorder traversal, deleting every node on each visit
			auto delete_node = [](const iterator& itor) {
				delete itor;
			};
			postorder_traversal(delete_node);
			root = nullptr;
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
			if(root != nullptr)
			{
				preorder(root, action);
			}
		}
		// Perform in-order traversal 
		// Call the function specified on each node visited
		void inorder_traversal(const node_action& action)
		{
			if(root != nullptr)
			{
				inorder(root, action);
			}
		}
		// Perform postorder traversal
		// Call the function specified on each node visited
		void postorder_traversal(const node_action& action)
		{
			if(root != nullptr)
			{
				postorder(root, action);
			}
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
				else if(key > current->key)
				{
					//...move to the right
					current = current->right;
				}
				// If the keys are equal, return nullptr
				// The tree cannot have duplicate keys!
				else
				{
					return nullptr;
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
		// (if any) point to that child as the parent
		void link_out(const iterator& rm)
		{
			// Grab all adjacent nodes
			iterator left = rm->left;
			iterator right = rm->right;
			iterator parent = rm->parent;

			if(parent != nullptr)
			{
				// Store if this is the left or right child
				bool isLeftChild = parent->left == rm;
				// Ground the corresponding child on the parent
				parent->ground_child(isLeftChild);
				// Link the child of the node on the same side of the parent
				// that this node is on
				if(left != nullptr)
				{
					parent->adopt_child(left, isLeftChild);
				}
				else if(right != nullptr)
				{
					parent->adopt_child(right, isLeftChild);
				}
			}
			// If iterator to remove has both children...
			if(left != nullptr && right != nullptr)
			{
				//...parent the right child on the rightmost descendent
				// node of the left node
				left->rightmost_descendent()->link_right(right);
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
			// If a right subtree exists, traverse it
			if(root->right != nullptr)
			{
				postorder(root->right, action);
			}
			// Perform the action last
			action(root);
		}
};

#endif // BINARY_TREE_H_
