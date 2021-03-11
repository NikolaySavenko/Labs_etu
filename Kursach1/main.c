#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

# define MAX_STRING_LEN 300
#define STR_END '\n'

#if defined(__linux) || defined(__linux__)
#define CLS system("clear")
#else
#define CLS system("cls")
#endif


int stringCountByLen(char *string, int len);

void clearWords(char *string, char *result, int n);

void filterWords(char *text);

char *readFromFile(FILE *df, int *s_count);

int new_gets(char *s, int lim, char endSymbol);

int main() {
	int state;
	int str_count;
	char *text = NULL;
	char endSymbol;
	int symbolsCount;

	do {
		puts("1: read via CLI");
		puts("2: read via input.txt");
		puts("3: About");
		puts("0: exit");
		scanf("%d", &state);

		switch (state) {
			case 1:
				CLS;
				puts("Chosen 1");
				puts("Symbols count:");
				scanf("%d", &symbolsCount);
				puts("'end' symbol:");
				getchar();
				scanf("%c", &endSymbol);
				text = (char *) malloc(symbolsCount * sizeof(char));
				puts("Input text:");
				new_gets(text, symbolsCount, endSymbol);
				CLS;
				puts("Source text:");
				puts(text);
				filterWords(text);
				puts("Updated text:");
				puts(text);
				getchar();
				break;
			case 2:
				CLS;
				puts("Chosen 2");
				text = readFromFile(fopen("input.txt", "r"), &str_count);
				printf("Find lines: %d %c", str_count, STR_END);
				printf("Source text: %s", text);
				filterWords(text);
				puts("\nUpdated text:");
				puts(text);
				getchar();
				break;
			case 3:
				CLS;
				puts("                              _     _\n"
					 "                             ( \\---/ )\n"
					 "                              ) . . (\n"
					 "________________________,--._(___Y___)_,--._______________________ \n"
					 "                        `--'           `--'");
				puts("About:");
				puts("Text filter for ETU");
				puts("Author: Nikolay Savenko");
				puts("Press F to pay respect");
				getchar();
				getchar();
				break;
			case 0:
				puts("Exit detected");
				getchar();
				break;
			default:
				puts("Incorrect key!");
				getchar();
				break;
		}
		puts("Press ENTER to continue");
		getchar();
		CLS;
	} while (state != 0);
	return 0;
}

char *readFromFile(FILE *df, int *s_count) {
	int i;
	char *text = NULL;
	int str_count = 1;
	int size;

	fseek(df, 0, SEEK_END);
	size = ftell(df);
	rewind(df);
	text = (char *) malloc(size * sizeof(char));
	if (text != NULL) {
		fread(text, size, 1, df);
		text[size - 1] = '\0';
		fclose(df);
		for (i = 0; i < size; i++) {
			if (text[i] == STR_END) {
				str_count++;
			}
		}
		*s_count = str_count;
	} else puts("Error at memory allocation for reading!");
	return text;
}

void filterWords(char *text) {
	int i;
	int count;
	int len;
	char current;
	char buffer[MAX_STRING_LEN] = "";
	count = 0;
	for (i = 0; i <= strlen(text); i++) {
		current = text[i];
		if (isspace(current) || ispunct(current) || current == '\0') {
			len = stringCountByLen(text, count);
			if (len >= 2) {
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
	int i, p;
	int count;
	char current;
	p = 0;
	count = 0;
	for (i = 0; i <= strlen(string); i++) {
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
	int i, p;
	int count;
	char current;
	p = 0;
	count = 0;
	for (i = 0; i <= strlen(string); i++) {
		current = string[i];
		if (isspace(current) || ispunct(current) || current == '\0') {
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

	int new_gets(char *s, int lim, char endSymbol) {
		char c;
		int i;
		for (i = 0; ((c = getchar()) != endSymbol) && (i < lim - 1); i++, s++) *s = c;
		*s = '\0';
		return i;
	}
