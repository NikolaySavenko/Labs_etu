#include <stdio.h>
#include <math.h>
/*
    2^x - 2 * e^(-x) = 0  solve to  0.00001
*/
float f(float x);

int main()
{
    float leftBorder, rigthBorder;

    scanf("%f %f", &leftBorder, &rigthBorder);
    printf("inputted values is %f %f \n\n\n\n\n", leftBorder, rigthBorder);
    printf("%f\n\n\n", f(leftBorder));

    return 0;
}

float f(float x) {
    return pow(2, x) - 2 * exp(-x);
}
