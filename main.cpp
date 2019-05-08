#include "pid.h"
#include <stdio.h>

int main(){
    pidControl pid = pidControl(0.1, 100, -100, 0.1, 0.01, 0.5);

    double mes = 20;
    double des = 0;

    for (int i = 0; i < 100; i++) {
        double inc = pid.calculate(des, mes);
        printf("%d. Desired: %.0f, Measured: %7.3f, Inc: %7.3f\n", i, des, mes, inc);
        mes += inc;
    }

    return 0;
}