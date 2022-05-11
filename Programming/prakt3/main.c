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

void delete_by_index(LHead *my_head, int index);

void swap(LHead *my_head, int index0, int index1);

int main() {
	duck *duckPtr = NULL;
	LHead head;
	char **s2 = NULL;
	char *string = NULL;
	int slen, i, j, count;
	int index0, index1;
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
			/*delete element by index*/
			puts("");
			puts("[DELETE_BY_INDEX]Delete element by index:");
			scanf("%d", &index0);

			delete_by_index(&head, index0);
			duckPtr = head.first;
			puts("[DELETE_BY_INDEX]After delete:");
			while (duckPtr != NULL) {
				printf("Source duck name: %s type %s pos: %d:%d w: %f h: %f paws %d wings %d this: %p\n ",
					   duckPtr->name,
					   duckPtr->type,
					   duckPtr->position[0],
					   duckPtr->position[1],
					   duckPtr->weight,
					   duckPtr->height,
					   duckPtr->paws_count,
					   duckPtr->wings_count,
					   (void *)duckPtr
				);
				duckPtr = duckPtr->next;
			}
			puts("");
			puts("[SWAP]Input index0");
			scanf("%d", &index0);
			puts("[SWAP]Input index1");
			scanf("%d", &index1);
			swap(&head, index0, index1);
			puts("[SWAP]Done");
			duckPtr = head.first;
			while (duckPtr != NULL) {
				printf("Source duck name: %s type %s pos: %d:%d w: %f h: %f paws %d wings %d this: %p\n ",
					   duckPtr->name,
					   duckPtr->type,
					   duckPtr->position[0],
					   duckPtr->position[1],
					   duckPtr->weight,
					   duckPtr->height,
					   duckPtr->paws_count,
					   duckPtr->wings_count,
					   (void *)duckPtr
				);
				duckPtr = duckPtr->next;
			}
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

/*Prakt3 tasks*/
void delete_by_index(LHead *my_head, int index) {
	int i = 0;
	duck  *duckPtr = my_head->first;
	if (index < my_head->count) {
		while (i < index) {
			duckPtr = duckPtr->next;
			i++;
		}
		/*target reached*/
		delete_node(my_head, duckPtr);
	} else puts("index > len; no element to delete");
}

void swap(LHead *my_head, int index0, int index1) {
	duck  *duckPtr0 = my_head->first;
	duck  *duckPtr1 = my_head->first;
	duck  tmpDuck;

	int i = 0;
	if (index0 < my_head->count && index1 < my_head->count) {
		while (i < index0) {
			duckPtr0 = duckPtr0->next;
			i++;
		}

		i = 0;
		/*target reached*/
		while (i < index1) {
			duckPtr1 = duckPtr1->next;
			i++;
		}

		tmpDuck.next = NULL;
		tmpDuck.weight = duckPtr0->weight;
		tmpDuck.name = duckPtr0->name;
		tmpDuck.type = duckPtr0->type;
		tmpDuck.wings_count = duckPtr0->wings_count;
		tmpDuck.paws_count = duckPtr0->paws_count;
		tmpDuck.height = duckPtr0->height;
		tmpDuck.position[0] = duckPtr0->position[0];
		tmpDuck.position[1] = duckPtr0->position[1];

		duckPtr0->weight = duckPtr1->weight;
		duckPtr0->name = duckPtr1->name;
		duckPtr0->type = duckPtr1->type;
		duckPtr0->wings_count = duckPtr1->wings_count;
		duckPtr0->paws_count = duckPtr1->paws_count;
		duckPtr0->height = duckPtr1->height;
		duckPtr0->position[0] = duckPtr1->position[0];
		duckPtr0->position[1] = duckPtr1->position[1];

		duckPtr1->weight = tmpDuck.weight;
		duckPtr1->name = tmpDuck.name;
		duckPtr1->type = tmpDuck.type;
		duckPtr1->wings_count = tmpDuck.wings_count;
		duckPtr1->paws_count = tmpDuck.paws_count;
		duckPtr1->height = tmpDuck.height;
		duckPtr1->position[0] = tmpDuck.position[0];
		duckPtr1->position[1] = tmpDuck.position[1];

		printf("Swapped %p <-> %p\n", (void *)duckPtr0, (void *)duckPtr1);
	} else puts("index > len; no element to swap");
}
