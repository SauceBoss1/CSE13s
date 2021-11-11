#include "numtheory.h"
#include "randstate.h"

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

void pow_mod(mpz_t o, mpz_t a, mpz_t d, mpz_t n) {
    mpz_t v;
    mpz_t p;
    mpz_t temp;
    mpz_inits(v, p, temp, NULL);

    mpz_set_ui(v, 1);
    mpz_set(p, a);
    while (mpz_cmp_ui(d, 0) > 0) {
        if (mpz_odd_p(d) != 0) {
            // v = (v*p) % n
            mpz_mul(temp, v, p);
            mpz_mod(v, temp, n);
        }
        //p = (p*p) % n
        mpz_mul(temp, p, p);
        mpz_mod(p, temp, n);

        //d = d/2
        mpz_fdiv_q_ui(d, d, 2);
    }

    mpz_set(o, v);
    mpz_clears(v, p, temp);
    return;
}

bool is_prime(mpz_t n, uint64_t iters) {
    //dealing with the simple edge cases first
    if ((mpz_cmp_ui(n, 1) <= 0) || (mpz_cmp_ui(n, 4) == 0)) {
        return false;
    }
    if ((mpz_cmp_ui(n, 3) <= 0)) {
        return true;
    }

    //find an r that is odd such that n = 2^s * r + 1
    mpz_t s;
    mpz_init(s);
    //s = n - 1
    mpz_sub_ui(s, n, 1);

    while (mpz_even_p(s) != 0) {
        //s /= 2
        mpz_fdiv_q_ui(s, s, 2);
    }

    mpz_t a, x, temp, y, n_minus_1, j, s_minus_1, two;
    mpz_inits(a, x, temp, y, n_minus_1, j, s_minus_1, two, NULL);

    //m-r primality testing algorithm
    for (uint64_t i = 1; i < iters; ++i) {
        //uint64_t a = (uint64_t) (rand() % ( n - 4 )) + 2;
        mpz_urandomm(a, state, n);
        mpz_sub_ui(temp, n, 3); //may need to change to 4
        mpz_mod(a, a, temp);
        mpz_add_ui(a, a, 2);

        //uint64_t y = pow_mod(a, s, n);
        pow_mod(y, a, s, n);

        mpz_sub_ui(n_minus_1, n, 1);
        mpz_sub_ui(s_minus_1, s, 1);
        mpz_set_ui(two, 2);

        //if( (y != 1) && (y != n - 1))
        if ((mpz_cmp_ui(y, 1) != 0) && (mpz_cmp(y, n_minus_1) != 0)) {
            mpz_set_ui(j, 1);

            //while ((j <= s - 1) && y != n - 1)
            while ((mpz_cmp(j, s_minus_1) <= 0) && (mpz_cmp(y, n_minus_1) != 0)) {
                //y = pow_mod(y, 2, n);
                pow_mod(y, y, two, n);

                //if (y == 1)
                if (mpz_cmp_ui(y, 1) == 0) {
                    return false;
                }
                //j = j + 1;
                mpz_add_ui(j, j, 1);
            }

            //if (y != n - 1)
            if (mpz_cmp(y, n_minus_1) != 0) {
                return false;
            }
        }
    }
    mpz_clears(s, a, x, temp, y, n_minus_1, j, s_minus_1, two);
    return true;
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    mpz_t temp;
    mpz_init(temp);

    do {
        mpz_urandomb(temp, state, bits);
    } while (is_prime(temp, iters));

    mpz_set(p, temp);
    mpz_clear(temp);
    return;
}

void gcd(mpz_t g, mpz_t a, mpz_t b) {
    //uint64_t t = 0;
    mpz_t t;
    mpz_init(t);
    mpz_set_ui(t, 0);

    while (mpz_cmp_ui(b, 0) != 0) {
        mpz_set(t, b);
        mpz_mod(b, a, b);
        mpz_set(a, t);
    }

    mpz_set(g, a);
    return;
}

void mod_inverse(mpz_t o, mpz_t a, mpz_t n) {
    mpz_t r, r_prime, t, t_prime, q, temp, mul_temp;
    mpz_inits(r, r_prime, t, t_prime, q, temp, mul_temp);

    //(r,r_prime)←(n,a)
    mpz_set(r, n);
    mpz_set(r_prime, a);

    //(t,t_prime)←(0,1)
    mpz_set_ui(t, 0);
    mpz_set_ui(t_prime, 1);

    //while r_prime != 0
    while (mpz_cmp_ui(r_prime, 0) != 0) {
        //q←r/r_prime
        mpz_fdiv_q(q, r, r_prime);

        //(r,r_prime)←(r_prime,r−q*r_prime)
        mpz_set(temp, r);
        mpz_set(r, r_prime);
        mpz_mul(mul_temp, q, r_prime);
        mpz_sub(r_prime, temp, mul_temp);

        //(t,t_prime)←(t_prime,t−q*t_prime)
        mpz_set(temp, t);
        mpz_set(t, t_prime);
        mpz_mul(mul_temp, q, t_prime);
        mpz_sub(t_prime, temp, mul_temp);
    }

    //if r > 1
    if (mpz_cmp_ui(r, 1) > 0) {
        //return no inverse
        mpz_set(o, 0);
        return;
    }

    //if t < 0
    if (mpz_cmp_ui(temp, 0) < 0) {
        //t←t+n
        mpz_add(t, t, n);
    }

    //return t
    mpz_set(o, t);

    mpz_clears(r, r_prime, t, t_prime, q, temp, mul_temp);
    return;
}

int main(void) {
    return 0;
}
