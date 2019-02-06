/*
 * cstr.h
 *
 *  Created on: Feb 2, 2019
 *      Author: creat
 */

#ifndef CSTR_H_
#define CSTR_H_

// O(n)
int strlen(const char*);
// O(n)
char* strcpy(char* dest, const char* src);
// O(n)
void* memchr(const void* block, int byte, int count);
// O(n^2)
char* strstr(char* haystack, const char* needle);
// O(n)
int strcmp(const char*, const char*);
// O(n)
char* strcat(const char* base, const char* add);

#endif /* CSTR_H_ */
