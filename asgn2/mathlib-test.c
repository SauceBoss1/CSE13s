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
        case 'a': a = e_num = b = m = r = v = n = s = true; break;
        case 'e': e_num = true; break;
        case 'n': n = true; break;
        case 'm': m = true; break;
        case 's': s = true; break;
        case 'r': r = true; break;
        case 'b': b = true; break;
        case 'v': v = true; break;
        case 'h': h = true; break;
        default: h = true; break;
        }
    }

    if (e_num) {
        //e();
        double diff = absolute(e() - M_E);
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, diff);
        if (s) {
            printf("e() terms = %d\n", e_terms());
        }
    }

    if (n) {
        for (double i = 0.0; i <= 10.0; i += 0.1) {
            double diff = absolute(sqrt_newton(i) - sqrt(i));
            printf("sqrt_newton(%lf) = %16.15lf, sqrt(%lf) = %16.15lf, diff = %16.15lf\n", i,
                sqrt_newton(i), i, sqrt(i), diff);
            if (s) {
                printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
            }
        }
    }

    if (m) {
        //pi_madhava();
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI,
            absolute(pi_madhava() - M_PI));
        if (s) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
    }

    if (r) {
        //pi_euler();
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI,
            absolute(pi_euler() - M_PI));
        if (s) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
    }

    if (b) {
        //pi_bbp();
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI,
            absolute(pi_bbp() - M_PI));
        if (s) {
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        }
    }

    if (v) {
        //pi_viete();
        printf("pi_viete() = %15.16lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI,
            absolute(pi_viete() - M_PI));
        if (s) {
            printf("pi_viete() terms = %d\n", pi_viete_factors());
        }
    }

    if (h) {
        puts("SYNOPSIS");
        puts("\tA test harness for the small numerical library.\n");
        puts("USAGE");
        puts("\t./mathlib-test [-aebmrvnsh]\n");
        puts("OPTIONS\n");
        puts("\t-a  Runs all tests.\n\t-e  Runs e test.\n\t-b  Runs BBP pi test.");
        puts("\t-m  Runs Madhava pi test.\n\t-r  Runs Euler pi test.\n\t-v  Runs Viete pi test.");
        puts("\t-n  Runs Newton square root tests.\n\t-s  Print verbose statistics.\n\t-h  Display "
             "program synopsis and usage.");
    }
    return 0;
}
