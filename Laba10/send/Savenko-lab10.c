#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 256

typedef struct DUCKNAME {
	int id;
	char *name;
	struct DUCKNAME *next;
} duckName;

typedef struct LHead {
	int count;
	duckName *first;
	duckName *last;
} LHead;

char **simple_split(char *str, int length, char sep);

void ClearStringArray(char **str, int n);

void delete_node(LHead *my_head, duckName *current_node);

void add_node(LHead *my_head, duckName *new_node);

void clear_list(LHead *my_head);

void delete_target(LHead *my_head);

int main() {
	duckName *namePtr = NULL;
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
			fseek(df, 0, SEEK_SET);
			for (i = 0; i < count; i++) {
				fgets(string, MAX_LEN, df);
				slen = strlen(string);
				string[slen - 1] = '\0';
				slen = strlen(string);

				s2 = simple_split(string, slen, sep);
				namePtr = (duckName *) malloc(sizeof(duckName));
				if (s2 != NULL && namePtr) {
					for (j = 0; j < 7; j++) {
						if (s2[j] == NULL) {
							for (i = j - 1; j >= 0; j--) free(s2[i]);
							i = count;
							j = 7;
						}
					}
					if (i != count) {
						namePtr->name = s2[0];
						namePtr->id = head.count;
						/*add*/
						add_node(&head, namePtr);
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
			fclose(df);
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

void clear_list(LHead *my_head)
{
	duckName *q,*q1;
	int i;
	q=my_head->first;
	for(i=0;i<my_head->count;i++)
	{
		q1=q->next;
		free(q);
		q=q1;
	}
}

void delete_target(LHead *my_head) {
	duckName *namePtr = NULL;
	int i;

	puts("Solution...");
	if (my_head->count > 1) {
		namePtr = my_head->first;
		while(namePtr->next != my_head->last)
		{
			namePtr = namePtr->next;
		}
		delete_node(my_head, namePtr);
	} else puts("Cant perform action");

	namePtr = my_head->first;
	puts("Finished list:");
	i = 0;
	while (i < my_head->count) {
		printf("Source duck name: %s \n ",
			   namePtr->name
		);
		namePtr = namePtr->next;
		i++;
	}
	clear_list(my_head);
}

void add_node(LHead *my_head, duckName *new_node)
{
	duckName *q=NULL;
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
			new_node->id=my_head->count;
			my_head->count++;
			new_node->next=q;
			my_head->first=new_node;
		}
	}
}

void delete_node(LHead *my_head, duckName *current_node)
{
	duckName *q, *q1;
	int i;
	q=my_head->first;
	q1=my_head->last;
	if(current_node==q)
	{
		my_head->first=current_node->next;
		q1->next=current_node->next;
		current_node->next=NULL;
		free(current_node);
		my_head->count--;
	}
	else
	{
		for(i=0;i<my_head->count;i++)
		{
			if(q->next==current_node)
			{
				if(current_node==q1) my_head->last=q;
				q->next=current_node->next;
				current_node->next=NULL;
				free(current_node);
				my_head->count--;
			}
			else q=q->next;
		}
	}
}
