#pragma once

class char_node
{
	public:
		char data;	// Data in the node
		char_node* next;	// Points to next node

		// Construct a node without a "next"
		char_node(char d)
		{
			data = d;
			next = nullptr;
		}

		// Given a node, the function "burrows" down the list to the nullptr,
		// producing a deep copy of every element on the way, and returns 
		// the head pointer of the list copied
		static char_node* digging_copy(char_node* start)
		{
			if(start == nullptr)
			{
				return nullptr;
			}

			char_node* copy = new char_node(start->data);
			copy->next = digging_copy(start->next);
			return copy;
		}

		// Delete this node and all nodes after it
		static void digging_delete(char_node* start)
		{
			char_node* previous = start;		
			char_node* current = start;

			while(current != nullptr)
			{
				// Advance current
				current = current->next;

				// Delete previous and move it to current
				delete prevoius;
				prevous = current;
			}
		}
}