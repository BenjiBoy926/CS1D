/*
 * cstr.cpp
 *
 *  Created on: Feb 2, 2019
 *      Author: creat
 */

int strlen(const char* ch)
{
	int count = 0;
	while(ch[count] != '\0')
	{
		count++;
	}
	return count;
}

char* strcpy(char* dest, const char* src)
{
	int index = -1;

	// Do-while ensures that the null terminator is also copied into the destination
	do // while(src[index] != '\0')
	{
		index++;
		dest[index] = src[index];
	} while(src[index] != '\0');

	return dest;
}

void* memchr(const void* block, int byte, int count)
{
	unsigned char* iterator = (unsigned char*)block;	// Interpret the memory block as unsigned chars
	void* found = nullptr;	// Pointer to the item in the memory block found
	int index = 0;	// Current index of the block being investigated

	// Interpret the byte as an unsigned char
	byte = (unsigned char)byte;

	// Loop until we find the byte or we've gone as far as the function allows
	while(found == nullptr && index < count)
	{
		// If this part of the block matches the byte...
		if(iterator[index] == byte)
		{
			//...assign a pointer to it
			found = &iterator[index];
		}
		index++;
	}

	return found;
}

char* strstr(char* haystack, const char* needle)
{
	char* tracker = haystack;	// Start the tracker pointer at the base address of the haystack
	int trackerIndex = 0;	// Index of the element in the haystack that the tracker is pointing to
	int siftingIndex = 0;	// Index used to simultaneously search the needle and haystack
	bool match = true;

	int needleLen = strlen(needle);
	int haystackLen = strlen(haystack);

	// If the needle is bigger than the haystack, return null
	if(needleLen > haystackLen)
	{
		return nullptr;
	}

	do // while(!match && tracker != nullptr);
	{
		// Find the first character of the needle in the haystack
		tracker = (char*)memchr(tracker, needle[0], haystackLen - trackerIndex);

		if(tracker != nullptr)
		{
			// Start up loop control variables
			match = true;
			siftingIndex = 0;

			// Check each character in the tracker with each character in the needle
			while(match && tracker[siftingIndex] != '\0' && needle[siftingIndex] != '\0')
			{
				match = tracker[siftingIndex] == needle[siftingIndex];
				siftingIndex++;
			}

			// If no match was found...
			if(!match)
			{
				//...start looking for the first character in the needle at the place after
				tracker++;
				// Calculate the index of the tracked item
				trackerIndex = (tracker - haystack) / sizeof(char);
			}
		}

	} while(!match && tracker != nullptr);

	return tracker;
}

int strcmp(const char* lhs, const char* rhs)
{
	int cmp = 0;
	int index = -1;

	do // while
	{
		// This means the comparison is allowed to compare the null terminator
		index++;
		cmp = lhs[index] - rhs[index];
	}while(cmp == 0 && lhs[index] != '\0' && rhs[index] != '\0');

	return cmp;
}

char* strcat(const char* base, const char* add)
{
	int baseLen = strlen(base);
	int addLen = strlen(add);
	char* newStr = new char[baseLen + addLen - 1];

	// Copy the base into the first part of the string
	strcpy(newStr, base);
	// Copy the add string starting at the end of the base string
	strcpy(&newStr[baseLen], add);

	return newStr;
}
