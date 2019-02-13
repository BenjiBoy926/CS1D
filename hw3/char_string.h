/*
 * char_string.h
 *
 *  Created on: Jan 29, 2019
 *      Author: chuntting0
 */

#pragma once

#include <iostream>
#include <algorithm>
#include "char_node.h"

class char_string
{
private:
	char_node* head;	// Points to the first node in the list

public:
	static int npos;

	char_string(const char* cstr = "")
	{
		head = nullptr;
		char_node* current = head;
		int index = 0;
		
		while(cstr[index] != '\0')
		{
			
		}
	}

	// Initialize the string from the base address of another string
	char_string(const char_node* otherHead)
	{
		head = char_node::digging_copy(otherHead);
	}

	// O(n)
	// n = size of other string
	char_string(const char_string& s)
	{
		*this = s;
	}

	// Basic assignment for deep copy
	// O(n)
	// n = size of other string
	char_string& operator=(const char_string& s)
	{
		erase();
		head = char_node::digging_copy(s.head);
		return *this;
	}
	// O(n)
	char& operator[](const int& index)
	{
		if(index < length())
		{
			char_node* target = head;

			// Loop up to the index, updating the target 
			for(int i = 1; i <= index; i++)
			{
				target = target->next;
			}

			// Return target's data
			return target->data;
		}
	}

	// O(n)
	int length() const
	{
		char_node* current = head;
		int length = 0;

		// Loop until a node is found that has no next pointer
		while(current != nullptr)
		{
			length++;
			current = current->next;
		}

		return length;
	}

	// O(n)
	// n = size of this string
	int indexOf(char search) const
	{
		char_node* current = head;
		int index = 0;
		bool found = false;

		while(!found && current != nullptr)
		{
			if(current->data == search)
			{
				found = true;
			}
			else
			{
				index++;
			}
		}

		return index;
	}
	// O(n^2)
	int indexOf(const char_string& search) const
	{
		std::cout << "\nWARNING: \"int indexOf(const char_string&)\" not implemented" << std::endl;
		return npos;
	}

	// O(n)
	// n = size of smaller string
	bool operator==(const char_string& s) const
	{
		// Check for uneven lengths at the start
		if(length() != s.length())
		{
			return false;
		}

		char_node* thisCurrent = head;
		char_node* otherCurrent = s.head;
		bool cmp = 0;

		while(cmp == 0 && thisCurrent != nullptr && otherCurrent != nullptr)
		{
			cmp = thisCurrent->data == otherCurrent->data;
			thisCurrent = thisCurrent->next;
			otherCurrent = otherCurrent->next;
		}

		return cmp;
	}
	// O(n)
	// n = size of resulting string
	char_string operator+(const char_string& s) const
	{
		// Produce digging copies of this list and other list
		char_node* firstChunk = char_node::digging_copy(head);
		char_node* secondChunk = char_node::digging_copy(s.head);

		// Points to the end of the first chunk
		char_node* firstEnd = firstChunk;
		while(firstEnd->next != nullptr)
		{
			firstEnd = firstEnd->next;
		}

		// End of first chunk now points to beginning of second chunk
		firstEnd->next = secondChunk;

		// Create a digging copy of the first chunk and delete the local copy
		char_string result(firstChunk);
		char_node::digging_delete(firstChunk);
		return result;
	}
	// O(n)
	// n = size of resulting string
	char_string& operator+=(const char_string& s)
	{
		*this = *this + s;
		return *this;
	}

	// O(n)
	// n = size of this string
	char_string reverse() const
	{
		std::cout << "\nWARNING: \"char_string reverse() const\" not implemented" << std::endl;
		return *this;
	}

	// O(n)
	// n = size of this string
	void print(std::ostream& out) const
	{
		char_node* current = head;

		while(current != nullptr)
		{
			out << current->data;
		}
	}
	// O(n)
	// n = size of this string
	void read(std::istream& in)
	{
		std::cout << "\nWARNING: \"void read(std::istream&)\" not implemented" << std::endl;
		return;
	}

	// O(n)
	~char_string()
	{
		erase();
	}

	// O(n)
	void erase()
	{
		char_node::digging_delete(head);
	}

	// Traverse through the list and return the node at the end
	char_node* end()
	{
		char_node* current = head;
		while(current != nullptr)
		{
			current = current->next;
		}
		return current;
	}
};

std::ostream& operator<<(std::ostream& out, const char_string& str)
{
	str.print(out);
	return out;
}
std::istream& operator>>(std::istream& in, char_string& str)
{
	str.read(in);
	return in;
}

int char_string::npos = -1;
