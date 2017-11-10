// 1.1 Is Unique: Implement an algorithm an algorithm to determine if a string
// has all unique characters. What if you cannot use additional data structures?

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define CHARSET_SIZE 128

// Returns 0 if string contains more characters than unique characters in the set
// Returns length of string otherwise
int isValid(char *string) {
	if(string == NULL)
		return -1;
	int length = strlen(string);
	return length > CHARSET_SIZE ? 0 : length;
}

int compare(const void *c1, const void *c2) {
	int *a = (int *) c1;
	int *b = (int *) c2;
	return *a - *b;
}

// Solution #1: Use an array
// Time: O(n), Memory: O(1)

int isUnique1(char *string) {
	int length = isValid(string);
	if(length == -1)
		return false;
	else if(length == 0)
		return true;
	int seen[CHARSET_SIZE] = {0};
	for(int c = 0; c < length; c++){
		int character = string[c];
		if(seen[character])
			return false;
		seen[character] = 1;
	}
	return true;
}

// Solution #2 (w/o data structure): Brute force
// Time: O(n^2), Memory: N/A

int isUnique2(char *string) {
	int length = isValid(string);
	if(length == -1)
		return false;
	else if(length == 0)
		return true;
	for(int c1 = 0; c1 < length; c1++) {
		for(int c2 = c1 + 1; c2 < length; c2++) {
			if(string[c1] == string[c2])
				return false;
		}
	}
	return true;
}

// Solution #3 (w/o data structure): Sort, then search
// Time: O(nlogn), Memory: N/A

int isUnique3(char *string) {
	int length = isValid(string);
	if(length == -1)
		return false;
	else if(length == 0)
		return true;
	char newString[length + 1];
	strcpy(newString, string);
	qsort(newString, length, sizeof(char), &compare);
	for(int c = 0; c < length - 1; c++) {
		if(newString[c] == newString[c + 1]) {
			return false;
		}
	}
	return true;
}

int main() {
	int numStrings = 4;
	char *strings[] = {"What's up?", "Hello", "", NULL};

	char *results[] = {"False", "True"};

	for(int s = 0; s < numStrings; s++) {
		int r1 = isUnique1(strings[s]);
		int r2 = isUnique2(strings[s]);
		int r3 = isUnique3(strings[s]);
		printf("String: %s\nIs Unique? %s %s %s\n\n", strings[s], results[r1], results[r2], results[r3]);
	}
	return 0;
}
