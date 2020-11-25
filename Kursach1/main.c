#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
# define MAX_STRING_LEN 300

int stringCountByLen(char* string, int len);
void clearWords(char* string, char* result, int n);
void filterWords(char* text);

int main() {
	char text[MAX_STRING_LEN] = "the Received the likewise law gracefull his";
	filterWords(text);
	printf("%s", text);
	return 0;
}

void filterWords(char *text) {
	int i;
	int count = 0;
	char current;
	char buffer[MAX_STRING_LEN] = "";
	for (i = 0; i <= strlen(text); i++){
		current = text[i];
		if (isspace(current) || current == '\0') {
			if (stringCountByLen(text, count) >= 2) {
				/* AHAHAHA*/
				clearWords(text, buffer, count);
				strcpy(text, buffer);
				i = -1;
			}
			count = 0;
		} else {
			count++;
		}
	}
}

void clearWords(char *string, char *result, int n) {
	int i, p = 0;
	int count = 0;
	char current;
	for (i = 0; i <= strlen(string); i++){
		current = string[i];
		if (isspace(current) || current == '\0') {
			if (count == n) {
				while (count > 0) {
					result[p - 1] = '\0';
					p--;
					count--;
				}
			} else {
				result[p] = current;
				p++;
				count = 0;
			}
		} else {
			result[p] = current;
			p++;
			count++;
		}
	}
}

int stringCountByLen(char *string, int len) {
	int i, p = 0;
	int count = 0;
	char current;
	for (i = 0; i <= strlen(string); i++){
		current = string[i];
		if (isspace(current) || current == '\0') {
			if (p == len) {
				count++;
			}
			p = 0;
		} else {
			p++;
		}
	}
	return count;
}
