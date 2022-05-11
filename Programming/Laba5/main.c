#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_STRING_LEN 128

int main() {
	char splitters[MAX_STRING_LEN];
	char string[MAX_STRING_LEN];
	int i = 0;
	int count = 0;
	int neededLen;
	int lastSplit = 0;
	printf("[WARNING] max string len is %d\n", MAX_STRING_LEN);
	printf("input splitters\n");
	fgets(splitters, MAX_STRING_LEN, stdin);
	printf("inputted splitters: %s\n\n", splitters);

	printf("input string\n");
	fgets(string, MAX_STRING_LEN, stdin);
	printf("inputted string: %s\n\n", string);

	printf("input needed len\n");
	scanf("%d", &neededLen);

	for (i = 0; i <= strlen(string); i++) {
		if (strchr(splitters, string[i]) != NULL || string[i] == '\0') {
			if (i - lastSplit == neededLen) {
				count++;
			}
			lastSplit = i + 1;
		}
	}
	printf("\nWords with len %d -> %d", neededLen, count);
	return 0;
}
