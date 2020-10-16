#include <stdio.h>
#include <stdlib.h>

int main()
{
    int k;
    int i = 0;
    int *arr;
    int len = 0;
	int buf = 0;
    
    printf("Len of array is ");
    scanf("%d", &len);

    arr = (int *)malloc(len * sizeof(int));
    while (i < len) {
        printf("%d element is: ", i);
        scanf("%d", &arr[i]);
        i++;
    }

    printf("Input K: ");
    scanf("%d", &k);

    buf = arr[len - 1];
    for(i = len - 2; i >= k; i--) {
    	arr[i + 1] = arr[i];
    }
    arr[k] = buf;

    printf("changed array is \n");
    for (i = 0; i < len; i++) {
		printf("%d ", arr[i]);
    }

    return 0;
}
