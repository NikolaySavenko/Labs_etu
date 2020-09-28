#include <stdio.h>
#include <math.h>
/*
    2^x - 2 * e^(-x) = 0  solve to  0.00001
*/
float f(float x);

int main()
{
    float lBorder, rBorder;

    scanf("%f %f", &lBorder, &rBorder);

    return 0;
}

float f(float x) {
    return pow(2, x) - 2 * exp(-x);
}
