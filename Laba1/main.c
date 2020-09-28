#include <stdio.h>
#include <math.h>
#define accuracy 0.00001

float func(float x);
int sign(float x);
int hasNeededAccuracy(float bound, float root);
int numLen(float x);
float getRelativeRoot(float a, float b);

int main()
{
    float lBorder, rBorder, relativeRoot;

    scanf("%f %f", &lBorder, &rBorder);
    relativeRoot  = getRelativeRoot(lBorder, rBorder);

    while (!hasNeededAccuracy(func(lBorder), func(relativeRoot))) {

        if (sign(func(relativeRoot)) != sign(func(rBorder))) {
            lBorder = relativeRoot;
        } else {
            rBorder = relativeRoot;
        }
        relativeRoot = getRelativeRoot(lBorder, rBorder);
    }

    printf("%f\n", relativeRoot);

    return 0;
}

float func(float x) {
    return pow(2, x) - 2 * exp(-x);
}

int hasNeededAccuracy(float bound, float root) {
    return (root - bound) < accuracy;
}

int numLen(float d) {
    int test = (int)d;
    int count = 0;
    while (test != d) {
        count++;
        d *= 10;
        test = (int)d;
    }
    return count;
}

float getRelativeRoot(float a, float b) {
    return (a + b) / 2;
}

int sign(float x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}
