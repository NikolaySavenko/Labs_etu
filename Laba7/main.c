#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 256
#define MAX_SUBSTRING_LEN 64

typedef struct DUCKDUCK {
	char *name;
	char *type;
	int position[2];
	float weight;
	float height;
	int paws_count;
	int wings_count;
} duck;

void sort_weight(struct DUCKDUCK *str0, int n);

char **simple_split(char *str, int length, char sep);

void ClearStringArray(char **str, int n);

int new_gets(char *s, int lim, char endSymbol);

int has_substring(char *str0, char *str1);

int main() {
	duck *ducks = NULL;
	char **s2 = NULL;
	char *string = NULL;
	char substring[MAX_LEN];
	int slen, i, j, count;
	int success;
	int choosen_type;
	char sep;
	FILE *df;
	int symbolsCount;
	success = 0;

	if ((string = (char *) malloc(MAX_LEN * sizeof(char) + 1)) != NULL) {
		if ((df = fopen("data.csv", "r")) != NULL) {
			sep = ';';
			count = 0;
			while (fgets(string, MAX_LEN, df)) {
				count++;
			}
			printf("Loaded %d ducks:\n", count);

			ducks = (duck *) malloc(count * sizeof(duck));
			fseek(df, 0, SEEK_SET);
			if (ducks != NULL) {
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
							ducks[i].name = s2[0];
							ducks[i].type = s2[1];
							ducks[i].position[0] = atoi(s2[2]);
							ducks[i].position[1] = atoi(s2[3]);
							ducks[i].weight = atof(s2[4]);
							ducks[i].height = atof(s2[5]);

							ducks[i].paws_count = atoi(s2[6]);
							ducks[i].wings_count = atoi(s2[7]);

							printf("Source duck #%d name: %s type %s pos: %d:%d w: %f h: %f paws %d wings %d\n ",
								   i,
								   ducks[i].name,
								   ducks[i].type,
								   ducks[i].position[0],
								   ducks[i].position[1],
								   ducks[i].weight,
								   ducks[i].height,
								   ducks[i].paws_count,
								   ducks[i].wings_count
							);
							success = 1;
							for (j = 2; j < 8; j++) free(s2[j]);
						} else puts("Out if memory! Program terminated");
					} else {
						puts("Out if memory! Program terminated");
						ClearStringArray(s2, 8);
					}
				}
				fclose(df);
			} else puts("Out if memory! Program terminated");
			/*From keyboard*/
			puts("Wants to add more?");
			puts("1 - yes; any key - no; ");
			while (getchar() == '1') {
				getchar();
				/*start*/
				ducks = (duck *) realloc(ducks, (count + 1) * sizeof(duck));
				puts("Input symbols count in name");
				scanf("%d", &symbolsCount);
				getchar();
				ducks[count].name = (char *) malloc(symbolsCount * sizeof(char));

				puts("Input symbols count in type");
				scanf("%d", &symbolsCount);
				getchar();
				ducks[count].type = (char *) malloc(symbolsCount * sizeof(char));

				if (ducks[count].name == NULL || ducks[count].type == NULL) {
					success = 0;
					puts("memory allocation error");
				} else {
					puts("Adding new duck with name:");
					new_gets(ducks[count].name, MAX_LEN, '\n');

					puts("With type:");
					new_gets(ducks[count].type, MAX_LEN, '\n');

					puts("Pos X of duck: ");
					scanf("%d", &ducks[count].position[0]);
					puts("Pos Y of duck: ");
					scanf("%d", &ducks[count].position[1]);
					puts("Weight of duck: ");
					scanf("%f", &ducks[count].weight);
					puts("Height of duck: ");
					scanf("%f", &ducks[count].height);
					puts("Paws count of duck: ");
					scanf("%d", &ducks[count].paws_count);
					puts("Wings count of duck: ");
					scanf("%d", &ducks[count].wings_count);
					getchar();

					printf("name: %s type %s pos: %d:%d w: %f h: %f paws %d wings %d\n ",
						   ducks[count].name,
						   ducks[count].type,
						   ducks[count].position[0],
						   ducks[count].position[1],
						   ducks[count].weight,
						   ducks[count].height,
						   ducks[count].paws_count,
						   ducks[count].wings_count
					);
					/*end*/
					count++;
					puts("Wants to add more?");
					puts("1 - yes; any key - no; ");
				}
			}

			/*Choose from substring*/
			if (success == 1) {
				puts("Find substring in:");
				puts("1 - name; 2 - type");
				scanf("%d", &choosen_type);
				getchar();

				printf("Input substring(max len: %d):", MAX_SUBSTRING_LEN);
				new_gets(substring, MAX_SUBSTRING_LEN, '\n');
				puts("Output:");
				sort_weight(ducks, count);
				for (i = 0; i < count; i++) {
					if (choosen_type == 1) {
						success = has_substring(ducks[i].name, substring) + 10;
					} else {
						success = has_substring(ducks[i].type, substring) + 10;
					}
					if (success > 10) {
						printf("name: %s type %s pos: %d:%d w: %f h: %f paws %d wings %d\n ",
							   ducks[i].name,
							   ducks[i].type,
							   ducks[i].position[0],
							   ducks[i].position[1],
							   ducks[i].weight,
							   ducks[i].height,
							   ducks[i].paws_count,
							   ducks[i].wings_count
						);
					}
					free(ducks[i].name);
					free(ducks[i].type);
					success = 2;
				}

				if (success != 2) {
					puts("Output is empty");
				}
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

void sort_weight(struct DUCKDUCK *str0, int n) {
	struct DUCKDUCK tmp_struct;
	int i, j;

	for (i = 0; i < n; i++) {
		tmp_struct = str0[i];
		for (j = i - 1; j >= 0 && str0[j].weight > tmp_struct.weight; j--) {
			str0[j + 1] = str0[j];
		}
		str0[j + 1] = tmp_struct;
	}
}

int new_gets(char *s, int lim, char endSymbol) {
	char c;
	int i;
	for (i = 0; ((c = getchar()) != endSymbol) && (i < lim - 1); i++, s++) *s = c;
	*s = '\0';
	return i;
}

int has_substring(char *str0, char *str1) {
	char *str0_copy = (char *) malloc(sizeof(str0));
	char *str1_copy = (char *) malloc(sizeof(str1));

	int i, len0, len1;
	len0 = (int) strlen(str0);
	len1 = (int) strlen(str1);
	strcpy(str0_copy, str0);
	strcpy(str1_copy, str1);

	for (i = 0; i < len0; i++) {
		str0_copy[i] = (char) tolower(str0_copy[i]);
	}
	for (i = 0; i < len1; i++) {
		str1_copy[i] = (char) tolower(str1_copy[i]);
	}
	return strstr(str0_copy, str1_copy) != NULL;
}
