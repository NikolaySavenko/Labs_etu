#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int a;
    int i = 0;
    int *arr;
    int len = 0;

    int lbi;
    int lb = 0;
    int rbi;
    int rb = 0;

    int nearestI = -1;
    int nearest = 0;

    printf("Len of array is ");
    scanf("%d", &len);

    arr = (int *)malloc(len * sizeof(int));
    while (i < len) {
        printf("%d element is: ", i);
        scanf("%d", &arr[i]);
        i++;
    }

    printf("Input A: ");
    scanf("%d", &a);

    rbi = len - 1;
    lbi = 0;

    i = 0;
    printf("a)");
    while (i < len && arr[i] < a) {
        printf(" %d ", arr[i]);
        i++;
    }

    i = 0;
    while (i < len && arr[i] < a) {
        lbi = i;
        lb = arr[lbi];
        rbi = i + 1;
        rb = arr[rbi];
        i++;
    }
    printf("\n b) left arr[%d] = %d; right arr[%d] = %d", lbi, lb, rbi, rb);

    while (a - lb < rb - a && nearestI < 0) {
          nearestI = lbi;
          nearest = lb;
    }
    while (nearestI < 0) {
        nearestI = rbi;
        nearest = rb;
    }

    printf("\n c) nearest is arr[%d] = %d", nearestI, nearest);
    return 0;
}
