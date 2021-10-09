#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "aebmrvnsh"

//The command-line program was first given to us by our TA Eugene
//The progam was then modified to fit this assignment
//
//The main() function handles and parses all command line options.
//The specific command line options will trigger specific calculations
//unless the user specifies -a then all calculations will be called.
//
//Returns 0 if prgram is a success.
//argc and argv: takes in a command line input
int main(int argc, char **argv) {
    bool a = false, e_num = false, b = false, m = false, r = false;
    bool v = false, n = false, s = false, h = false;
    int opt = 0;

    while (
        (opt = getopt(argc, argv, OPTIONS)) != -1) { //this checks if the a valid option is eneterd
        //else the loop ends
        switch (opt) { //this checks what option was called
        case 'a': a = e_num = b = m = r = v = n = s = true; break; //calls all functions
        case 'e': e_num = true; break; //calls the calculation for e
        case 'n': n = true; break; //calls the calculation for newton's sqrt
        case 'm': m = true; break; //calls the madhava series calculation
        case 's': s = true; break; //enables showing the stats for each calculation
        case 'r': r = true; break; //calls the Euler's solution calculation
        case 'b': b = true; break; //calls bbp calculation
        case 'v': v = true; break; //calls the viete calculation
        case 'h': h = true; break; //displays the help message
        default: h = true; break;
        }
    }

    if (e_num) { //displays a formated output for Euler's number with a comparison to M_E
        //e();
        double diff = absolute(e() - M_E);
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, diff);
        if (s) {
            printf("e() terms = %d\n", e_terms());
        }
    }

    if (n) { //displays a series of formatted newtpm's square root tests
        for (double i = 0.0; i <= 10.0;
             i += 0.1) { //tests and compares a series of newton_sqrt and sqrt tests
            double diff = absolute(sqrt_newton(i) - sqrt(i));
            printf("sqrt_newton(%lf) = %16.15lf, sqrt(%lf) = %16.15lf, diff = %16.15lf\n", i,
                sqrt_newton(i), i, sqrt(i), diff);
            if (s) {
                printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
            }
        }
    }

    if (m) { //displays a formatted output for the madhava series and comapres it to M_PI
        //pi_madhava();
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI,
            absolute(pi_madhava() - M_PI));
        if (s) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
    }

    if (r) { //displays a formatted output for Euler's solution and compares it M_PI
        //pi_euler
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI,
            absolute(pi_euler() - M_PI));
        if (s) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
    }

    if (b) { // displays a formatted output for the bbp formaula and compares it to M_PI
        //pi_bbp();
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI,
            absolute(pi_bbp() - M_PI));
        if (s) {
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        }
    }

    if (v) { //displays a formatted output for the viete formaula and comapres it to M_PI
        //pi_viete();
        printf("pi_viete() = %15.16lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI,
            absolute(pi_viete() - M_PI));
        if (s) {
            printf("pi_viete() terms = %d\n", pi_viete_factors());
        }
    }

    if (h) { //displays a help message
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
