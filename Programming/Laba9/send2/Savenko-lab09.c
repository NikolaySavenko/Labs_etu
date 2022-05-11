#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 256

typedef struct DUCKNAME {
	int id;
	char *name;
	struct DUCKNAME *next;
	struct DUCKNAME *prev;
} duckName;

typedef struct LHead {
	int count;
	duckName *first;
	duckName *last;
} LHead;

typedef struct DUCKDUCK {
	duckName *name;
	char *type;
	int position[2];
	float weight;
	float height;
	int paws_count;
	int wings_count;
} duck;

void clear_list(LHead *my_head);

char **simple_split(char *str, int length, char sep);

void ClearStringArray(char **str, int n);

int new_gets(char *s, int lim, char endSymbol);

void delete_node(LHead *my_head, duckName *current_node);

void delete_target(LHead *my_head, duck *ducks, int capacity);

int main() {
	duck *ducks = NULL;
	duckName *duckNamePtr = NULL;
	LHead head;
	char **s2 = NULL;
	char *string = NULL;
	int slen, i, j, count;
	int success;
	char sep;
	FILE *df;
	success = 0;
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


			ducks = (duck *) malloc(count * sizeof(duck));
			fseek(df, 0, SEEK_SET);
			if (ducks != NULL) {
				for (i = 0; i < count; i++) {
					fgets(string, MAX_LEN, df);
					slen = strlen(string);
					string[slen - 1] = '\0';
					slen = strlen(string);

					s2 = simple_split(string, slen, sep);
					duckNamePtr = (duckName *) malloc(sizeof(duckName));
					if (s2 != NULL && duckNamePtr) {
						for (j = 0; j < 7; j++) {
							if (s2[j] == NULL) {
								for (i = j - 1; j >= 0; j--) free(s2[i]);
								i = count;
								j = 7;
							}
						}
						if (i != count) {
							duckNamePtr->name = s2[0];
							duckNamePtr->id = head.count;
							if (head.first == NULL) {
								head.first = duckNamePtr;
								head.first->next = NULL;
								head.first->prev = NULL;
								head.last = duckNamePtr;
							} else {
								duckNamePtr->prev = head.last;
								head.last->next = duckNamePtr;
								head.last = duckNamePtr;
							}
							head.count++;
							success = 1;
							for (j = 2; j < 8; j++) free(s2[j]);
						} else {
							puts("Out if memory! Program terminated");
							clear_list(&head);
							ClearStringArray(s2, 8);
						}
					} else {
						puts("Out if memory! Program terminated");
						ClearStringArray(s2, 8);
						clear_list(&head);
					}
				}
				fseek(df, 0, SEEK_SET);
				if (success == 1) {
					for (i = 0; i < count; i++) {
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
								duckNamePtr = head.first;
								while (strcmp(duckNamePtr->name, s2[0]) != 0) {
									/*yeah, its 100% works. Because we 100% know that one of list has name == s2[0]*/
									duckNamePtr = duckNamePtr->next;
								}
								ducks[i].name = duckNamePtr;
								ducks[i].type = s2[1];
								ducks[i].position[0] = atoi(s2[2]);
								ducks[i].position[1] = atoi(s2[3]);
								ducks[i].weight = atof(s2[4]);
								ducks[i].height = atof(s2[5]);

								ducks[i].paws_count = atoi(s2[6]);
								ducks[i].wings_count = atoi(s2[7]);
								success = 1;
								for (j = 2; j < 8; j++) free(s2[j]);
							} else {
								puts("Out if memory! Program terminated");
								clear_list(&head);
								ClearStringArray(s2, 8);
							}
						} else {
							puts("Out if memory! Program terminated");
							ClearStringArray(s2, 8);
							clear_list(&head);
						}
					}
				} else {
					puts("Out if memory! Program terminated");
					ClearStringArray(s2, 8);
					clear_list(&head);
				}
				fclose(df);
			} else {
				puts("Out if memory! Program terminated");
				clear_list(&head);
			}

			delete_target(&head, ducks, count);

			for (i = 0; i < count; i++) {
				if (ducks[i].type != NULL) free(ducks[i].type);
				success = 2;
			}
		}
	}

	if (ducks != NULL) {
		free(ducks);
	}

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


int new_gets(char *s, int lim, char endSymbol) {
	char c;
	int i;
	for (i = 0; ((c = getchar()) != endSymbol) && (i < lim - 1); i++, s++) *s = c;
	*s = '\0';
	return i;
}

void clear_list(LHead *my_head) {
	duckName *q, *q1;
	q = my_head->first;
	while (q != NULL) {
		q1 = q->next;
		free(q);
		q = q1;
	}
}

void delete_target(LHead *my_head, duck *ducks, int capacity) {
	duckName *duckName = NULL;
	char *choosenName = (char *) malloc(MAX_LEN * sizeof(char));
	int success = 0;
	int i = 0;
	printf("Loaded %d ducks:\n", capacity);
	for (i = 0; i < capacity; i++) {
		printf("Source duck id:%d name: %s type %s pos: %d:%d w: %f h: %f paws %d wings %d\n ",
			   i,
			   ducks[i].name->name,
			   ducks[i].type,
			   ducks[i].position[0],
			   ducks[i].position[1],
			   ducks[i].weight,
			   ducks[i].height,
			   ducks[i].paws_count,
			   ducks[i].wings_count
		);
	}
	puts("Solution");
	printf("Delete element with name[max:%d]:", MAX_LEN);
	new_gets(choosenName, MAX_LEN, '\n');
	duckName = my_head->first;

	while (duckName != NULL) {
		if (strcmp(duckName->name, choosenName) == 0) {
			if (duckName->next == NULL) {
				puts("Cant perform action");
				duckName = NULL;
			} else {
				for (i = 0; i < capacity; i++) {
					if (strcmp(duckName->next->name, ducks[i].name->name) == 0) {
						free(ducks[i].type);
						ducks[i].type = NULL;
						/*type NULL means that duck is deleted*/
					}
				}
				delete_node(my_head, duckName->next);
				success = 2;
				duckName = NULL;
			}
		} else {
			duckName = duckName->next;
		}
	}
	if (success != 2) puts("No elements found");

	puts("Finished list:");

	for (i = 0; i < capacity; i++) {
		if (ducks[i].type != NULL) {
			printf("Source duck id:%d name: %s type %s pos: %d:%d w: %f h: %f paws %d wings %d\n ",
				   i,
				   ducks[i].name->name,
				   ducks[i].type,
				   ducks[i].position[0],
				   ducks[i].position[1],
				   ducks[i].weight,
				   ducks[i].height,
				   ducks[i].paws_count,
				   ducks[i].wings_count
			);
		}
	}
	clear_list(my_head);
}

void delete_node(LHead *my_head, duckName *current_node) {
	duckName *q, *q1, *q2, *q3;
	q = my_head->first;
	q1 = my_head->last;
	if (current_node == q) {
		q2 = current_node->next;
		my_head->first = q2;
		q2->prev = NULL;
		current_node->next = NULL;
		free(current_node);
	} else {
		while (q != NULL) {
			if (q->next == current_node) {
				q2 = current_node->prev;
				if (current_node == q1) {
					my_head->last = q2;
					q2->next = NULL;
				} else {
					q3 = current_node->next;
					q2->next = q3;
					q3->prev = q2;
				}
				current_node->next = NULL;
				current_node->prev = NULL;
				free(current_node);
			} else q = q->next;
		}
	}
	my_head->count--;
}
