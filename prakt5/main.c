#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 256

typedef struct DUCKDUCK {
	int id;
	struct DUCKDUCK *next;
	char *name;
	char *type;
	int position[2];
	float weight;
	float height;
	int paws_count;
	int wings_count;
} duck;

void push(duck **top, duck *new_element);

duck *pop(duck** top);

int array_length(duck *top);

void array_clear(duck *top);

void print_not_even_pos_x(duck *top);

void print_by_name_symbol(duck *top);

char **simple_split(char *str, int length, char sep);

int new_gets(char *s, int lim, char endSymbol);

void ClearStringArray(char **str, int n);

int main() {
	duck *duckPtr = NULL;
	duck *top = NULL;
	char **s2 = NULL;
	char *string = NULL;
	int slen, i, j, count;
	char sep;
	FILE *df;

	if ((string = (char *) malloc(MAX_LEN * sizeof(char) + 1)) != NULL) {
		if ((df = fopen("data.csv", "r")) != NULL) {
			sep = ';';
			count = 0;
			while (fgets(string, MAX_LEN, df)) {
				count++;
			}
			printf("Loaded %d duckPtr:\n", count);
			fseek(df, 0, SEEK_SET);
			for (i = 0; i < count; i++) {
				duckPtr = (duck *) malloc(sizeof(duck));
				if (duckPtr != NULL) {
					fgets(string, MAX_LEN, df);
					slen = strlen(string);
					string[slen - 1] = '\0';
					slen = strlen(string);

					s2 = simple_split(string, slen, sep);
					if (s2 != NULL) {
						for (j = 0; j < 7; j++) {
							if (s2[j] == NULL) {
								for (i = j - 1; j >= 0; j--) free(s2[i]);
								i = count;
								j = 7;
							}
						}
						if (i != count) {
							duckPtr->name = s2[0];
							duckPtr->type = s2[1];
							duckPtr->position[0] = atoi(s2[2]);
							duckPtr->position[1] = atoi(s2[3]);
							duckPtr->weight = atof(s2[4]);
							duckPtr->height = atof(s2[5]);

							duckPtr->paws_count = atoi(s2[6]);
							duckPtr->wings_count = atoi(s2[7]);
							duckPtr->next = NULL;

							/*add to list*/

							push(&top, duckPtr);
							for (j = 2; j < 8; j++) free(s2[j]);
						} else {
							puts("mem alloc err");
							array_clear(top);
						}
					} else {
						puts("Out if memory! Program terminated");
						array_clear(top);
					}
				} else {
					puts("Out if memory! Program terminated");
					ClearStringArray(s2, 8);
					array_clear(top);
				}
			}
			fclose(df);

			puts("");
			puts("In Stack:");
			duckPtr = top;
			i = 0;
			while (duckPtr != NULL) {
				printf("Source duck #%d name: %s type %s pos: %d:%d w: %f h: %f paws %d wings %d\n ",
					   duckPtr->id,
					   duckPtr->name,
					   duckPtr->type,
					   duckPtr->position[0],
					   duckPtr->position[1],
					   duckPtr->weight,
					   duckPtr->height,
					   duckPtr->paws_count,
					   duckPtr->wings_count
				);
				duckPtr = duckPtr->next;
				i++;
			}

			puts("");
			puts("[print_not_even_pos_x]");
			print_not_even_pos_x(top);

			puts("");
			puts("[print_by_name_symbol]");
			print_by_name_symbol(top);

			array_clear(top);
		}
	} else puts("memory alloc error");

	return 0;
}

void ClearStringArray(char **str, int n) {
	int i;

	for (i = 0; i < n; i++) {
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}

char **simple_split(char *str, int length, char sep) {
	char **str_array = NULL;
	int i, j, k, m;
	int key, count;
	for (j = 0, m = 0; j < length; j++) {
		if (str[j] == sep) m++;
	}

	key = 0;
	str_array = (char **) malloc((m + 1) * sizeof(char *));
	if (str_array != NULL) {
		for (i = 0, count = 0; i <= m; i++, count++) {
			str_array[i] = (char *) malloc(length * sizeof(char));
			if (str_array[i] != NULL) key = 1;
			else {
				key = 0;
				i = m;
			}
		}
		if (key) {
			k = 0;
			m = 0;
			for (j = 0; j < length; j++) {
				if (str[j] != sep) str_array[m][j - k] = str[j];
				else {
					str_array[m][j - k] = '\0';
					k = j + 1;
					m++;
				}
			}
		} else {
			ClearStringArray(str_array, count);
		}
	}
	return str_array;
}

void push(duck **top, duck *new_element) {
	new_element->id = array_length(*top);

	new_element->next=*top;
	*top=new_element;
}

duck *pop(duck **top) {
	duck *tmp=NULL;
	if(*top)
	{
		tmp=*top;
		*top = tmp->next;
	}
	return tmp;
}

int array_length(duck *top) {
	duck *tmp;
	int i;
	i=0;
	if(top)
	{
		tmp=top;
		while(tmp)
		{
			tmp=tmp->next;
			i++;
		}
	}
	return i;
}

void array_clear(duck *top) {
	duck *duckPtr = pop(&top);
	while (duckPtr != NULL) {
		free(duckPtr->name);
		free(duckPtr->type);
		free(duckPtr);
		duckPtr = pop(&top);
	}
}

int new_gets(char *s, int lim, char endSymbol) {
	char c;
	int i;
	for (i = 0; ((c = getchar()) != endSymbol) && (i < lim - 1); i++, s++) *s = c;
	*s = '\0';
	return i;
}

/*Prakt5 solve*/
void print_by_name_symbol(duck *top) {
	duck *duckPtr = NULL;
	char *symbols = NULL;
	int symbols_count = 0;
	int i = 0;
	int j = 0;

	puts("Input symbols count");
	scanf("%d", &symbols_count);
	getchar();

	if (symbols_count > 0) {
		symbols = (char *) malloc(sizeof(char) * symbols_count);
		if (symbols != NULL) {
			puts("Input symbols string");
			new_gets(symbols, symbols_count + 1, '\n');

			duckPtr = top;
			while (duckPtr != NULL) {
				i = 0;
				while (i < strlen(symbols)) {
					j = 0;
					while (j < strlen(duckPtr->name)) {
						if (duckPtr->name[j] == symbols[i]) {
							printf("Source duck #%d name: %s type %s pos: %d:%d w: %f h: %f paws %d wings %d\n ",
								   duckPtr->id,
								   duckPtr->name,
								   duckPtr->type,
								   duckPtr->position[0],
								   duckPtr->position[1],
								   duckPtr->weight,
								   duckPtr->height,
								   duckPtr->paws_count,
								   duckPtr->wings_count
							);
							j = strlen(duckPtr->name);
							i = strlen(symbols);
						}
						j++;
					}
					i++;
				}
				duckPtr = duckPtr->next;
			}
			free(symbols);
		} else puts("Mem alloc error");
	} else puts("symbols count should be > 0");
}

void print_not_even_pos_x(duck *top) {
	duck *duckPtr = top;
	while (duckPtr != NULL) {
		if (duckPtr->position[0] % 2 != 0) {
			printf("Source duck #%d name: %s type %s pos: %d:%d w: %f h: %f paws %d wings %d\n ",
				   duckPtr->id,
				   duckPtr->name,
				   duckPtr->type,
				   duckPtr->position[0],
				   duckPtr->position[1],
				   duckPtr->weight,
				   duckPtr->height,
				   duckPtr->paws_count,
				   duckPtr->wings_count
			);
		}
		duckPtr = duckPtr->next;
	}
}
