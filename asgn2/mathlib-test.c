#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "aebmrvnsh"

int main(int argc, char **argv) {
    bool a = false, e_num = false, b = false, m = false, r = false;
    bool v = false, n = false, s = false, h = false;
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': a = e_num = b = m = r = v = n = s = h = true; break;
        case 'e': e_num = true; break;
        case 'n': n = true; break;
        case 'm': m = true; break;
        case 's': s = true; break;
        case 'r': r = true; break;
        }
    }

    if (e_num) {
        double diff = absolute(e() - M_E);
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, diff);
        if (s) {
            printf("e() terms = %d\n", e_terms());
        }
    }

    if (n) {
        for (double i = 0.0; i <= 10.0; i += 0.1) {
            double diff = absolute(sqrt_newton(i) - sqrt(i));
            printf("sqrt_newton(%lf) = %16.15lf sqrt(%lf) = %16.15lf diff = %16.15lf\n", i,
                sqrt_newton(i), i, sqrt(i), diff);
            if (s) {
                printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
            }
        }
    }

    if (m) {
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI,
            absolute(pi_madhava() - M_PI));
        if (s) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
    }

    if (r) {
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI,
            absolute(pi_euler() - M_PI));
        if (s) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
    }
    return 0;
}
