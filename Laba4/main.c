#include <stdlib.h>
#include <stdio.h>

void printArray(int **arr, int n, int m);
int *makeColumn(int *line, int n);

int main() {
	int n = 0;
	int m = 0;
	int i = 0;
	int j = 0;
	int b = 0;
	int *buffer = NULL;
	int **matrix = NULL;
	int **matrix2 = NULL;
	puts("array size X");
	scanf("%d", &n);
	puts("array size Y");
	scanf("%d", &m);

	matrix = (int**)malloc(n * sizeof(int*));
	matrix2 = (int**)malloc(m * sizeof(int*));

	if (matrix != NULL && matrix2 != NULL) {
		for (i = 0; i < n; i++) {
			matrix[i] = (int*)malloc(m * sizeof(int));
			if (matrix[i] == NULL) {
				puts("Error at memory allocation!! Try again.");
				for (j = i - 1; j >= 0; j--) free(matrix[j]);
				n = 0;
				m = 0;
			}

			for (j = 0; j < m; j++) {
				printf("matrix[%d][%d] = ", i, j);
				scanf("%d", &matrix[i][j]);
			}
		}
		printArray(matrix, n, m);

		for (i = 0; i < m; i++) {
			matrix2[i] = (int*)malloc(n * sizeof(int));
			if (matrix2[i] == NULL) {
				puts("Error at memory allocation!! Try again.");
				for (j = i - 1; j >= 0; j--) free(matrix2[j]);
				for (i = 0; i < n; i++) free(matrix[i]);

				n = 0;
				m = 0;
			}
		}
		for (i = 0; i < n; i++) {
			buffer = makeColumn(matrix[i], m);
			if (buffer != NULL) {
				for (j = 0; j < m; j++) {
					matrix2[j][b] = buffer[j];
				}
				b++;
			}
		}
		printArray(matrix2, m, b);

		for (i = 0; i < n; i++) free(matrix[i]);
		for (i = 0; i < m; i++) free(matrix2[i]);
	} else puts("Error at memory allocation!! Try again.");
	/* if memory allocated for matrix or matrix2 */
	if (matrix != NULL) free(matrix);
	if (matrix2 != NULL) free(matrix2);
	return 0;
}

int *makeColumn(int *line, int n) {
	int *column = (int*)malloc(n * sizeof(int));
	int i = 0;
	int lstDiv = -1;
	if (column != NULL) {
		for (i = 0; i < n; i++) {
			column[i] = line[n - i - 1];
			if (column[i] % 2 == lstDiv) {
				column = NULL;
				i = n;
			} else lstDiv = column[i] % 2;
		}
	}
	return column;
}

void printArray(int **arr, int n, int m) {
	int i, j;
	if (n > 0 && m > 0) {
		printf("Matrix created %dx%d\n", n, m);
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				printf("%5d", arr[i][j]);
			}
			puts("");
		}
	} else puts("Matrix for print not exist");
}
