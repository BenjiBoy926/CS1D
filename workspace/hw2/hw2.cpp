/*
 * hw2.cpp
 *
 *  Created on: Jan 29, 2019
 *      Author: chuntting0
 */

#include "hw2.h"

int main()
{
	testCharConstructor();
	testAssignment();
	testIndexer();
	testIndexOf();
	testEquivalence();
	testAdding();

	return 0;
}

void testCharConstructor()
{
	char_string full("Hello world!");
	char_string empty;

	std::cout << "Testing char* constructors:\n";
	std::cout << "---------------------------\n";
	std::cout << "Filled string: " << full << std::endl;
	std::cout << "Empty string:  " << empty << std::endl << std::endl;
}

void testAssignment()
{
	char_string first("Do we match?");
	char_string second;
	second = first;

	std::cout << "Testing assignment:\n";
	std::cout << "-------------------\n";
	std::cout << "Initialized string: " << first << std::endl;
	std::cout << "Assigned string:    " << second << std::endl << std::endl;
}

void testIndexer()
{
	char_string str("Duke");
	const int index = 2;
	char& ch = str[index];
	char newChar = 'd';

	std::cout << "Testing indexing:\n";
	std::cout << "-----------------\n";
	std::cout << "String: " << str << std::endl;
	std::cout << "Character at " << index << ": " << ch << std::endl;
	std::cout << "Changing character at " << index << " to " << newChar << "...\n";
	str[index] = newChar;
	std::cout << "Modified string: " << str << std::endl << std::endl;
}

void testIndexOf()
{
	const char_string str("Hello World!");
	const char charFind = 'W';
	const char charMiss = 'w';
	const char_string strFind("World");
	const char_string strMiss("Wrld");

	std::cout << "Testing index of:\n";
	std::cout << "-----------------\n";
	std::cout << "Index of \"" << charFind << "\" in \"" << str << "\": " << str.indexOf(charFind) << std::endl;
	std::cout << "Index of \"" << charMiss << "\" in \"" << str << "\": " << str.indexOf(charMiss) << std::endl;
	std::cout << "Index of \"" << strFind << "\" in \"" << str << "\": " << str.indexOf(strFind) << std::endl;
	std::cout << "Index of \"" << strMiss << "\" in \"" << str << "\": " << str.indexOf(strMiss) << std::endl << std::endl;
}

void testEquivalence()
{
	const char_string str1("ABC");
	const char_string str2("ABC");
	const char_string str3("DEF");

	std::cout << "Testing equivalence:\n";
	std::cout << "--------------------\n";
	std::cout << str1 << " and " << str2 << " are ";
	if(!(str1 == str2))
	{
		std::cout << "NOT ";
	}
	std::cout << "equal\n";
	std::cout << str1 << " and " << str3 << " are ";
	if(!(str1 == str3))
	{
		std::cout << "NOT ";
	}
	std::cout << "equal\n\n";
}

void testAdding()
{
	char_string str1("Hello");
	char_string str2("World");

	std::cout << "Testing string adding:\n";
	std::cout << "----------------------\n";
	std::cout << str1 << " + " << str2 << " = " << (str1 + str2) << std::endl;
	std::cout << "Str1 before +=: " << str1 << std::endl;
	str1 += str1;
	std::cout << "Str1 after +=:  " << str1 << std::endl << std::endl;
}

char_string copyConstructorTest(char_string l)
{
	return l;
}

//void testReverse()
//{
//	std::ifstream in("input.txt");
//	char_string l;
//
//	// what tha frick?!
//	while(in >> 1)
//	{
//		std::cout << copyConstructorTest(l) << ' ' << l.length() << ' ' << l.reverse() << std::endl;
//	}
//}
