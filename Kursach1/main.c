#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

# define MAX_STRING_LEN 300

#if defined(_WIN32) || defined(__CYGWIN__)
	# define STR_END '\r\n'
#elif defined(__linux__)
	# define STR_END '\n'
#elif defined(__APPLE__) && defined(__MACH__)
    # define STR_END '\r'
#elif defined(unix) || defined(__unix__) || defined(__unix)
    # define STR_END '\n'
#else
    #error Unknown environment!
#endif

int stringCountByLen(char *string, int len);
void clearWords(char *string, char *result, int n);
void filterWords(char *text);
char* readFromFile(FILE *df, int* s_count);
int new_gets(char *s, int lim);

int main() {
	char state = 0;
	int i, j, k;
	int str_count = 1, count;
	int tsize, cur_pos;
	char *text = NULL;
	char **str_arr = NULL;
	int need_lines;
	FILE *df;

	str_count = 0;
	count = 0;
	df = fopen("input.txt", "r");
	puts("file");
	do {
		puts("1: read via CLI");
		puts("2: read via input.txt");
		puts("4: exit");
		state = (char) getchar();

		/*system("cls");*/
		if (state == '1') {
			puts("Text:");
			text  = (char *) malloc(need_lines * sizeof(char));
			new_gets(text, MAX_STRING_LEN);
			puts("Source text:");
			puts(text);
			filterWords(text);
			puts("Updated text:");
			puts(text);
		} else if (state == '2') {
			puts("Chosen 2");
			text = readFromFile(df, &str_count);
			printf("Find lines: %d %c", str_count, STR_END);
			puts("Source text:");
			puts(text);
			filterWords(text);
			puts("Updated text:");
			puts(text);
		}
	} while (state != '2');
	return 0;
}

char* readFromFile(FILE *df, int* s_count) {
	int cur_pos, i, j, k;
	int count = 0;
	char *text = NULL;
	char **target = NULL;
	char c0;
	int str_count = 1;
	long tsize;

	fseek(df , 0 , SEEK_END);
	tsize = ftell(df);
	rewind(df);
	text = (char *) malloc(tsize * sizeof(char));
	if (text != NULL) {
		fread(text, tsize, 1, df);
		text[tsize - 1] = '\0';
		fclose(df);
		for (i = 0; i < tsize; i++) {
			if (text[i] == STR_END) str_count++;
		}
		*s_count = str_count;
		/*printf("\nNumber of strings: %d\n", str_count);
		puts("-----------------------------");
		puts("Processing results:");
		puts("-----------------------------");*/
		target = (char **) malloc(str_count * sizeof(char *));
		/*if (target != NULL) {
			cur_pos = 0;
			i = 0;
			for (k = 0; k < str_count; k++) {
				for (i = cur_pos; text[i] != STR_END && text[i] != EOF - 3; i++) {}
				j = i - cur_pos;
				target[k] = (char *) malloc(j * sizeof(char));
				if (target[k] != NULL) {
					count++;
					for (i = 0; i < j + 1; i++) target[k][i] = text[cur_pos + i];
					target[k][j] = '\0';
					cur_pos = cur_pos + i;
				} else {
					k = str_count;
				}
			}
		} else puts("Error at memory allocation for processing!");*/
	} else puts("Error at memory allocation for reading!");

	/*for (i = 0; i < count; i++) {
		free(str_arr[i]);
		str_arr[i] = NULL;
	}
	if (str_arr != NULL) {
		free(str_arr);
		str_arr = NULL;
	}*/
	/*if (text != NULL) free(text);*/
	return text;
}
void filterWords(char *text) {
	int i;
	int count = 0;
	char current;
	char buffer[MAX_STRING_LEN] = "";
	for (i = 0; i <= strlen(text); i++) {
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
	int i, p = 0;
	int count = 0;
	char current;
	for (i = 0; i <= strlen(string); i++) {
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
int new_gets(char *s, int lim) {
	char c;
	int i;
	for(i=0;((c=getchar())!='0')&&(i<lim-1);i++,s++) *s=c;
	*s='\0';
	return i;
}

