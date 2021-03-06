#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define GOAL_SIZE 150

struct person {
	char *name;
	struct animosity *likes;
	struct person *next;
};

struct animosity {
	char *towards;
	long amount;
	struct animosity *next;
};

char *AddToString(char *, long long *, char);
long choose(long *, int, int, int);

int main (void)
{
	long long allocSize = 80;
	char *buffer = calloc(allocSize, sizeof(char));
	int numAlloced = 2;
	long *vals = calloc(1, sizeof(long));
	int numVals = 0;
	char c;
	while ((c = fgetc(stdin)) && !feof(stdin)){
		if (c == '\n') { // POSIX!!!!!!
			vals[numVals++] = strtol(buffer, NULL, 10);
			if (numVals >= numAlloced) {
				numAlloced *= 2;
				vals = realloc(vals, numAlloced*sizeof(long));
			}
			memset(buffer, 0, allocSize);
		} else {
			buffer = AddToString(buffer, &allocSize, c);
		}
	}
	printf("Arrangements: %ld\n", choose(vals, 0, numVals, 0));
	return 0;
}

char *AddToString(char *str, long long *strAllocSize, char add)
{
	long len = strlen(str);
	if (len + 2 >= *strAllocSize) {
		*strAllocSize *= 2;
		str = realloc(str, sizeof(char)*(*strAllocSize));
		if (!str) {
			fprintf(stderr, "Out of memory for string!\n");
			exit(1);
		}
	}
	if (str) { 
		str[len] = add; 
		str[len+1] = 0; 
	}
	return str; 
}

/* curr is the current index to choose and size is sizeof vals */
long choose(long *vals, int curr, int size, int curTotal)
{
	long subMatches = 0;
	if (curTotal > GOAL_SIZE) {
		return 0;
	} else if (curTotal == GOAL_SIZE) {
		return 1;
	}
	if (curr == size-1) { // Final condition
		if (curTotal + vals[curr] == GOAL_SIZE) {
			return 1;
		}
		return 0;
	}
	subMatches += choose(vals, curr+1, size, curTotal);
	subMatches += choose(vals, curr+1, size, curTotal+vals[curr]);
	return subMatches;
}
