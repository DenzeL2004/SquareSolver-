#include <stdio.h>
#include <math.h>
#include <TXLib.h>
#include "Squaref.h"

int main(){
    printf ("Enter the coefficients a, b, c of the second degree equation ax^2+bx+c = 0\n");

    double a = NAN, b = NAN, c = NAN;

    if (!read_arguments (&a, &b, &c))
        return 0;

    double x1 = NAN, x2 = NAN;
    char T = ANOTHER, count_roots = 0;
    count_roots = solve (a, b, c, &x1, &x2, &T);
    write_result (count_roots, x1, x2);

    getchar();
    return 0;
}
