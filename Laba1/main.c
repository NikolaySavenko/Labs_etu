#include <stdio.h>
#include <math.h>
#define accuracy 0.00001

float func(float x);
int sign(float x);
int hasNeededAccuracy(float bound, float root);
float getRelativeRoot(float a, float b);

int main()
{
    float lBorder, rBorder, relativeRoot;
    int lBorderSign, rBorderSign;
    scanf("%f %f", &lBorder, &rBorder);
    relativeRoot  = getRelativeRoot(lBorder, rBorder);

    while (!hasNeededAccuracy(func(lBorder), func(relativeRoot))) {
        lBorderSign = sign(func(relativeRoot));
        rBorderSign = sign(func(rBorder));
        if (lBorderSign != rBorderSign) {
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

float getRelativeRoot(float a, float b) {
    return (a + b) / 2;
}

int sign(float x) {
    int output = 0;
    if (x > 0) output = 1;
    if (x < 0) output = -1;
    return output;
}
