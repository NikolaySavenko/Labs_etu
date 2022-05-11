#include <stdlib.h>
#include <stdio.h>

int main() {
	int n, i, j, sum0 = 0, sum1 = 0, sum2 = 0, sum3 = 0;
	int **matrix = NULL;
	scanf("%d", &n);

	matrix = (int**)malloc(n * sizeof(int*));

	if (matrix != NULL) {
		for (i = 0; i < n; i++) {
			matrix[i] = (int*)malloc(n * sizeof(int));

			for (j = 0; j < n; j++) {
				scanf("%d", &matrix[i][j]);
			}
		}

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if(i != j && n - i - 1 != j) {
					if (i < j) {
						if (i < n - j - 1) sum0 += matrix[i][j];
						else matrix[i][j] = sum1 += matrix[i][j];
					} else {
						if (i < n - j - 1) sum3 += matrix[i][j];
						else sum2 += matrix[i][j];
					}
				}
			}
		}

		for (i = 0; i < n; i++) free(matrix[i]);
		free(matrix);

		printf("%d %d %d %d", sum0, sum1, sum2, sum3);

	} else puts("Error at memory allocation!! Try again.");
	return 0;
}
