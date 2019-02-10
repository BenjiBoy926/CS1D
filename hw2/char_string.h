/*
 * char_string.h
 *
 *  Created on: Jan 29, 2019
 *      Author: chuntting0
 */

#pragma once

#include <iostream>
#include <algorithm>
#include "cstr.h"

class char_string
{
private:
	char* data;
	int strLen;

public:
	static int npos;

	// Constructors
	// O(n)
	// n = size of c-string in parameter
	char_string(const char* ch = "")
	{
		strLen = strlen(ch);
		data = new char[strLen + 1];
		strcpy(data, ch);
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
		// If data has been allocated, delete it
		if(data != nullptr)
		{
			delete [] data;
		}

		strLen = s.strLen;
		data = new char[strLen + 1];
		strcpy(data, s.data);
		return *this;
	}
	// O(1)
	char& operator[](const int& index)
	{
		return data[index];
	}

	// O(1)
	int length() const
	{
		return strLen;
	}

	// O(n)
	// n = size of this string
	int indexOf(char search) const
	{
		// Get a pointer to the element searching for
		const char* found = (char*)memchr(data, search, strLen);

		// If the character was found...
		if(found != nullptr)
		{
			//...calculate the difference between the address of the found character
			// and the head address of the array
			return (found - data) / sizeof(char);
		}
		// If the character was NOT found...
		else
		{
			//...return an invalid value
			return npos;
		}
	}
	// O(n^2)
	int indexOf(const char_string& search) const
	{
		// Get a pointer to the element searching for
		const char* found = strstr(data, search.data);

		// If we found it, return the difference between found and data addresses for the index
		if(found != nullptr)
		{
			return (found - data) / sizeof(char);
		}
		// If we didn't find it, return invalid value
		else
		{
			return npos;
		}
	}

	// O(n)
	// n = size of smaller string
	bool operator==(const char_string& s) const
	{
		return strcmp(data, s.data) == 0;
	}
	// O(n)
	// n = size of resulting string
	char_string operator+(const char_string& s) const
	{
		// Produce a deep copy of the concatenated string, then delete it
		char* cattedString = strcat(data, s.data);
		char_string result(cattedString);
		delete [] cattedString;
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
		char* copy = new char[strLen + 1];
		strcpy(copy, data);
		std::reverse(copy, copy + strLen);

		return char_string(copy);
	}

	// O(n)
	// n = size of this string
	void print(std::ostream& out) const
	{
		out << data;
	}
	// O(n)
	// n = size of this string
	void read(std::istream& in)
	{
		for(int i = 0; i < strLen; i++)
		{
			in >> data[i];
		}
	}

	// O(1)
	~char_string()
	{
		if(data != nullptr)
		{
			delete [] data;
		}
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
