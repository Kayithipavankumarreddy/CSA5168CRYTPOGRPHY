#include <stdio.h>
#include <math.h>

int main() {

    double log2_factorial = 0.0;

    for (int i = 1; i <= 25; i++) {
        log2_factorial += log2(i);
    }

    printf("log2(25!) = %.2lf\n", log2_factorial);
    printf("Approximate power of 2: 2^%.2lf\n", log2_factorial);

    return 0;
}