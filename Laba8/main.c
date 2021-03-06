#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 256
#define MAX_SUBSTRING_LEN 64

typedef struct DUCKDUCK {
	struct DUCKDUCK *next;
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

void delete_node(LHead *my_head, duck *current_node);

void clear_list(LHead *my_head);

void delete_target(LHead *my_head);

int main() {
	duck *duckPtr = NULL;
	LHead head;
	char **s2 = NULL;
	char *string = NULL;
	int slen, i, j, count;
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

							if (head.first == NULL) {
								head.first = duckPtr;
								head.first->next = NULL;
								head.last = duckPtr;
							} else {
								head.last->next = duckPtr;
								head.last = duckPtr;
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
			duckPtr = head.first;
			puts("In list:");
			while (duckPtr != NULL) {
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
				duckPtr = duckPtr->next;
			}
			/*task solution*/
			delete_target(&head);
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

void delete_node(LHead *my_head, duck *current_node) {
	duck *q, *q1;
	q = my_head->first;
	q1 = my_head->last;
	if (current_node == q) {
		my_head->first = current_node->next;
		current_node->next = NULL;
		free(current_node);
	} else {
		while (q != NULL) {
			if (q->next == current_node) {
				if (current_node == q1) my_head->last = q;
				q->next = current_node->next;
				current_node->next = NULL;
				free(current_node);
			} else q = q->next;
		}
	}
	my_head->count--;
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

void delete_target(LHead *my_head) {
	duck *duckPtr = NULL;
	int choosen_value;
	int success = 0;
	puts("Delete element with X position:");
	scanf("%d", &choosen_value);
	duckPtr = my_head->first;
	puts("Solution");
	while (duckPtr != NULL) {
		if (duckPtr->position[0] == choosen_value) {
			if (duckPtr->next == NULL) {
				puts("Cant perform action");
				duckPtr = NULL;
			} else {
				delete_node(my_head, duckPtr->next);
				success = 2;
				duckPtr = NULL;
			}
		} else duckPtr = duckPtr->next;
	}
	if (success != 2) puts("No elements found");

	duckPtr = my_head->first;
	puts("Finished list:");
	while (duckPtr != NULL) {
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
		duckPtr = duckPtr->next;
	}
	clear_list(my_head);
}
