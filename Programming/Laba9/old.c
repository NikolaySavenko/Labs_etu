#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 256

typedef struct DUCKDUCK {
	struct DUCKDUCK *next;
	struct DUCKDUCK *prev;
	int Xpos;
} duck;

typedef struct LHead {
	int count;
	duck *first;
	duck *last;
} LHead;

char **simple_split(char *str, int length, char sep);

void ClearStringArray(char **str, int n);

void delete_node(LHead *my_head, duck *current_node);

void add_node(LHead *my_head, duck *new_node);

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
							duckPtr->Xpos = atoi(s2[2]);
							duckPtr->next = NULL;

							printf("Source duck Xpos: %d \n ",
								   duckPtr->Xpos
							);

							if (head.first == NULL) {
								head.first = duckPtr;
								head.first->next = NULL;
								head.first->prev = NULL;
								head.last = duckPtr;
							} else {
								duckPtr->prev = head.last;
								head.last->next = duckPtr;
								head.last = duckPtr;
							}
							head.count++;
							/*add_node(&head, duckPtr);*/
							ClearStringArray(s2, 8);
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
				printf("Source duck Xpos: %d \n ",
					   duckPtr->Xpos
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
	duck *q,*q1,*q2,*q3;
	q=my_head->first;
	q1=my_head->last;
	if(current_node==q)
	{
		q2=current_node->next;
		my_head->first=q2;
		q2->prev=NULL;
		current_node->next=NULL;
		free(current_node);
	}
	else
	{
		while(q!=NULL)
		{
			if(q->next==current_node)
			{
				q2=current_node->prev;
				if(current_node==q1)
				{
					my_head->last=q2;
					q2->next=NULL;
				}
				else
				{
					q3=current_node->next;
					q2->next=q3;
					q3->prev=q2;
				}
				current_node->next=NULL;
				current_node->prev=NULL;
				free(current_node);
			}
			else q=q->next;
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
		if (duckPtr->Xpos== choosen_value) {
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
		printf("Source duck Xpos: %d \n ",
			   duckPtr->Xpos
		);
		duckPtr = duckPtr->next;
	}
	clear_list(my_head);
}

void add_node(LHead *my_head, duck *new_node) {
	duck *q=NULL;
	int k;
	if(my_head&&new_node)
	{
		q=my_head->first;
		if(q==NULL)
		{
			my_head->count=1;
			my_head->first=new_node;
			my_head->last=new_node;
			new_node->next=my_head->first;
		}
		else
		{
			my_head->count++;
			new_node->next=q;
			my_head->first=new_node;
		}
	}
}
