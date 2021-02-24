#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 256

struct GROUP2 {
	char *Name;
	int DAT[3];
	int SES[3];
};
typedef struct GROUP2 stud;

void sort_rating(struct GROUP2 *str0, int n);

char **simple_split(char *str, int length, char sep);

void ClearStringArray(char **str, int n);

int main() {
	stud *studs = NULL;
	char **s2 = NULL;
	char s1[MAX_LEN];
	char *string = NULL;
	int slen, i, j, count;
	int success;
	char sep;
	FILE *df;
	success = 0;

	if ((string = (char *) malloc(MAX_LEN * sizeof(char) + 1)) != NULL) {
		if ((df = fopen("data.csv", "r")) != NULL) {
			sep = ';';
			count = 0;
			while (fgets(string, MAX_LEN, df)) {
				count++;
			}
			printf("Finded %d students:\n", count);

			studs = (stud *) malloc(count * sizeof(stud));
			fseek (df, 0, SEEK_SET);
			if (studs != NULL) {
				for (i = 0; i < count; i++) {
					fgets(s1, MAX_LEN, df);
					slen = strlen(s1);
					s1[slen - 1] = '\0';
					slen = strlen(s1);

					s2 = simple_split(s1, slen, sep);
					if (s2 != NULL) {
						for (j = 0; j < 7; j++) {
							if (s2[j] == NULL) {
								for (i = j - 1; j >= 0; j--) free(s2[i]);
								i = count;
								j = 7;
							}
						}
						if (i != count) {
							studs[i].Name = s2[0];
							studs[i].DAT[0] = atoi(s2[1]);
							studs[i].DAT[1] = atoi(s2[2]);
							studs[i].DAT[2] = atoi(s2[3]);

							studs[i].SES[0] = atoi(s2[4]);
							studs[i].SES[1] = atoi(s2[5]);
							studs[i].SES[2] = atoi(s2[6]);
							printf("Name: %s Dat %d.%d.%d SES: %d, %d, %d\n ",
								   studs[i].Name,
								   studs[i].DAT[0],
								   studs[i].DAT[1],
								   studs[i].DAT[2],
								   studs[i].SES[0],
								   studs[i].SES[1],
								   studs[i].SES[2]
							);
							success = 1;
							for (j = 1; j < 7; j++) free(s2[j]);
						} else puts("Out if memory! Program terminated");
					} else {
						puts("Out if memory! Program terminated");
						ClearStringArray(s2, 7);
					}
				}
				fclose(df);
			} else puts("Out if memory! Program terminated");

			if (success == 1) {
				puts("Output:");
				sort_rating(studs, count);
				for (i = 0; i < count; i++) {
					if (studs[i].DAT[0] > 1997 || (
							studs[i].DAT[0] == 1997 && studs[i].DAT[2] >= 1
					)) {
						success = 2;
						printf("Name: %s Dat %d.%d.%d SES: %d, %d, %d\n ",
							   studs[i].Name,
							   studs[i].DAT[0],
							   studs[i].DAT[1],
							   studs[i].DAT[2],
							   studs[i].SES[0],
							   studs[i].SES[1],
							   studs[i].SES[2]
						);
					}
					free(studs[i].Name);
				}
				if (success == 1) {
					puts("Output is empty");
				}
				free(studs);
			}
		}
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

void sort_rating(struct GROUP2 *str0, int n) {
	struct GROUP2 tmp_struct;
	int i, j;

	for (i = 0; i < n; i++) {
		tmp_struct = str0[i];
		for (j = i - 1; (j >= 0) &&
						(str0[j].SES[0] + str0[j].SES[1] + str0[j].SES[2] >
						 tmp_struct.SES[0] + tmp_struct.SES[1] + tmp_struct.SES[2]);
			 j--) {
			str0[j + 1] = str0[j];
		}
		str0[j + 1] = tmp_struct;
	}
}
