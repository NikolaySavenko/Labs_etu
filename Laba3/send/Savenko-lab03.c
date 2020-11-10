#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {
	int n, rndBound, i, j;
	int sum0 = 0;
	int sum1 = 0;
	int sum2 = 0;
	int sum3 = 0;
	int **matrix = NULL;
	srand(time(NULL));

	printf("Input matrix size\n");
	scanf("%d", &n);
	printf("Input upper random bound(under is always 0)\n");
	scanf("%d", &rndBound);

	matrix = (int**)malloc(n * sizeof(int*));

	if (matrix != NULL) {
		for (i = 0; i < n; i++) {
			matrix[i] = (int*)malloc(n * sizeof(int));
			if (matrix[i] == NULL) {
				puts("Error at memory allocation!! Try again.");
				for (j = i - 1; j >= 0; j++) {
					free(matrix[j]);
				}
				free(matrix);
				n = 0;
			}

			for (j = 0; j < n; j++) {
				/* random numbers from 0 to rndBound */
				matrix[i][j] = rand() % rndBound;
			}
		}

		printf("Matrix created\n");
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				printf("%5d", matrix[i][j]);
			}
			puts("");
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

		puts("Sums is:");
		printf("%5d\n%d %5d \n%5d", sum0, sum3, sum1, sum2);

	} else puts("Error at memory allocation!! Try again.");
	return 0;
}
