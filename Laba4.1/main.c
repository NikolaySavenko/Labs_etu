#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

void printLine(int *line, int m);
int getEvenInColumn(int **array, int n, int m);

int main() {
	int *a = NULL;
	int **array = NULL;
	int **array2 = NULL;
	int i, j, n, needEven, elem, m, count, arr2Len = 0;
	printf("Enter the number of lines: ");
	scanf("%d", &n);
	printf("Enter the number of even numbers in the column: ");
	scanf("%d", &needEven);
	i = 0;
	m = 0;
	count = 0;
	do {
		scanf("%d", &elem);
		a = (int *) realloc(a, (i + 1) * sizeof(int));
		if (a != NULL) {
			a[i] = elem;
			m++;
			i++;
		} else {
			puts("Memory allocation error");
			elem = -1;
			n = 0;
			m = 0;
		}
	} while (elem >= 0);

	array = (int **) malloc(n * sizeof(int *));
	array2 = (int **) malloc(n * sizeof(int *));
	if (array != NULL && array2 != NULL) {
		array[0] = (int *) malloc(m * sizeof(int));
		array2[0] = (int *) malloc(m * sizeof(int));

		if (array[0] != NULL && array2[0] != NULL) {
			array[0] = a;

			for (i = 1; i < n; i++) {
				array[i] = (int *) malloc(m * sizeof(int));
				array2[i] = (int *) malloc(m * sizeof(int));
				if (array[i] != NULL && array2[i] != NULL) {
					for (j = 0; j < m; j++) {
						scanf("%d", &array[i][j]);
					}
				} else {
					puts("Memory allocation error");
					for (i = i - 1; i >= 0; i--) free(array[i]);
					for (i = i - 1; i >= 0; i--) free(array2[i]);
					n = 0;
					m = 0;
				}
			}

			puts("Input Array is:");
			for (i = 0; i < n; i++) {
				printLine(array[i], m);
			}

			for (i = 0; i < m; i++) {
				if (getEvenInColumn(array, n, i) == needEven) {
					arr2Len++;
					for (j = 0; j < n; j++) {
						array2[j][arr2Len - 1] = array[j][i];
					}
				}
			}
			puts("New Array is:");
			for (i = 0; i < n; i++) {
				printLine(array2[i], arr2Len);
			}
		} else puts("Memory allocation error");
	} else puts("Memory allocation error");

	for (i = n - 1; i >= 0; i--) free(array[i]);
	for (i = n - 1; i >= 0; i--) free(array2[i]);

	if (array != NULL) free(array);
	if (array2 != NULL) free(array2);
	return 0;
}

void printLine(int *line, int m) {
	int i;
	for (i = 0; i < m; i++) {
		printf("%4d", line[i]);
	}
	puts("");
}

int getEvenInColumn(int **array, int n, int m) {
	int count = 0;
	int j;
	for (j = 0; j < n; j++) {
		if (array[j][m] % 2 == 0) count++;
	}
	return count;
}
