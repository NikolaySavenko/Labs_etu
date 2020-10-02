#include <stdio.h>
#include <math.h>
#define e 0.00001

int main()
{
    float a, fa, b, c, fc;
    scanf("%f %f", &a, &b);
    c = (a + b) / 2;
    while ((b - a) > e) {
        fa = pow(2, a) - 2 * exp(-a);
        fc = pow(2, c) - 2 * exp(-c);
        if (fa * fc < 0) {
            b = c;
        } else {
            a = c;
        }
        c = (a + b) / 2;
    }

    printf("%f", c);

    return 0;
}
