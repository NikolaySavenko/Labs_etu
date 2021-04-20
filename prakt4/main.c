#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 256
#define MAX_SUBSTRING_LEN 64

typedef struct DUCKDUCK {
	int id;
	struct DUCKDUCK *next;
	struct DUCKDUCK *prev;
	char *name;
	char *type;
	int position[2];
	float weight;
	float height;
	int paws_count;
	int wings_count;
} duck;

typedef struct LHead {
	int count;
	duck *first;
	duck *last;
} LHead;

char **simple_split(char *str, int length, char sep);

void ClearStringArray(char **str, int n);

void clear_list(LHead *my_head);

duck *searchById(duck **head, int id);

void showRevert(LHead *head);

int main() {
	duck *duckPtr = NULL;
	LHead head;
	char **s2 = NULL;
	char *string = NULL;
	int slen, i, j, count;
	int index0;
	char sep;
	FILE *df;
	head.count = 0;
	head.first = NULL;
	head.last = NULL;

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

							printf("Source duck #%d name: %s type %s pos: %d:%d w: %f h: %f paws %d wings %d\n ",
								   i,
								   duckPtr->name,
								   duckPtr->type,
								   duckPtr->position[0],
								   duckPtr->position[1],
								   duckPtr->weight,
								   duckPtr->height,
								   duckPtr->paws_count,
								   duckPtr->wings_count
							);
							/*add to list*/
							duckPtr->id = head.count;
							if (head.first == NULL) {
								head.first = duckPtr;
								head.first->next = head.first;
								head.first->prev = head.first;
								head.last = duckPtr;
							} else {
								duckPtr->prev = head.last;
								head.last->next = duckPtr;
								head.last = duckPtr;
								head.last->next = head.first;
								head.first->prev = head.last;
							}
							head.count++;
							for (j = 2; j < 8; j++) free(s2[j]);
						} else {
							puts("mem alloc err");
							clear_list(&head);
						}
					} else {
						puts("Out if memory! Program terminated");
						clear_list(&head);
					}
				} else {
					puts("Out if memory! Program terminated");
					ClearStringArray(s2, 8);
					clear_list(&head);
				}
			}
			fclose(df);

			puts("");
			puts("[FIND_BY_INDEX]Find element by index:");
			scanf("%d", &index0);
			duckPtr = searchById(&head.first, index0);
			if (duckPtr == NULL) puts("No element");
			else printf("Source duck name: %s type %s pos: %d:%d w: %f h: %f paws %d wings %d\n ",
				   duckPtr->name,
				   duckPtr->type,
				   duckPtr->position[0],
				   duckPtr->position[1],
				   duckPtr->weight,
				   duckPtr->height,
				   duckPtr->paws_count,
				   duckPtr->wings_count
			);

			puts("");
			puts("[SHOW_REWERT]");
			showRevert(&head);
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

void clear_list(LHead *my_head)
{
	duck *q,*q1;
	q=my_head->first;
	while(q!=NULL)
	{
		q1=q->next;
		free(q);
		q=q1;
	}
}

/*Prakt4 tasks*/
duck *searchById(duck **head, int id) {
	duck* duckPtr = *head;
	while (duckPtr->next != *head && duckPtr->id != id) {
		duckPtr = duckPtr->next;
	}
	if (duckPtr->id != id) {
		duckPtr = NULL;
	}
	return duckPtr;
}

void showRevert(LHead *head) {
	duck* duckPtr = head->last;
	int count = head->count;
	/*sorry, code is poor, but its work)*/
	while (count > 0) {
		printf("Source duck name: %s type %s pos: %d:%d w: %f h: %f paws %d wings %d\n ",
			   duckPtr->name,
			   duckPtr->type,
			   duckPtr->position[0],
			   duckPtr->position[1],
			   duckPtr->weight,
			   duckPtr->height,
			   duckPtr->paws_count,
			   duckPtr->wings_count
		);
		count--;
		duckPtr = duckPtr->prev;
	}
}

