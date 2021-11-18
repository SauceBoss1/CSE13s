#include "numtheory.h"
#include "randstate.h"

#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

//Calculate the power modulus of a^d mod n
//Returns a void
//
//Takes in mpz_t values instead of pure integers
//NOTE: algorithm pseudocode was provided in assignment doc
void pow_mod(mpz_t o, mpz_t a, mpz_t d, mpz_t n) {
    mpz_t v, p, temp, a_temp, d_temp, n_temp;
    mpz_inits(v, p, temp, a_temp, d_temp, n_temp, NULL);

    //setting the inputs to temp vars so that
    //we dont override the inputs
    mpz_set(a_temp, a);
    mpz_set(d_temp, d);
    mpz_set(n_temp, n);

    mpz_set_ui(v, 1);
    mpz_set(p, a_temp);
    while (mpz_cmp_ui(d_temp, 0) > 0) {
        if (mpz_odd_p(d_temp) != 0) {
            // v = (v*p) % n
            mpz_mul(temp, v, p);
            mpz_mod(v, temp, n_temp);
        }
        //p = (p*p) % n
        mpz_mul(temp, p, p);
        mpz_mod(p, temp, n_temp);

        //d = d/2
        mpz_fdiv_q_ui(d_temp, d_temp, 2);
    }

    //"returning" the final result
    mpz_set(o, v);
    mpz_clears(v, p, temp, a_temp, d_temp, n_temp, NULL);
    return;
}

//Determine whether or not the mpz_t n is a prime number or not
//This algorithm uses the Miller-Rabin test
//This test is not 100% correct but it is close enough
//
//Returns true if n is a prime, false otherwise
//
//n: the number to test
//iters: how many iterations of the algorithm we will use
//NOTE: algorithm pseudocode was provided in assignment doc
bool is_prime(mpz_t n, uint64_t iters) {
    //dealing with the simple edge cases first
    if ((mpz_cmp_ui(n, 1) <= 0) || (mpz_cmp_ui(n, 4) == 0)) {
        return false;
    }
    if ((mpz_cmp_ui(n, 3) <= 0)) {
        return true;
    }

    mpz_t n_temp;
    mpz_init(n_temp);
    mpz_set(n_temp, n);

    mpz_t a, x, temp, y, n_minus_1, j, s_minus_1, two, r;
    mpz_inits(a, x, temp, y, n_minus_1, j, s_minus_1, two, r, NULL);

    mpz_sub_ui(n_minus_1, n_temp, 1);
    mpz_set_ui(two, 2);

    mpz_set_ui(r, 0);
    mp_bitcnt_t s = 0;

    //Find an (n-1)/(2^s) = r such that r is odd
    do {
        mpz_fdiv_q_2exp(r, n_minus_1, s);
        s++;
    } while (!mpz_even_p(r));
    s--;

    mpz_fdiv_q_2exp(r, n_minus_1, s); //this gives us the final value of r

    //m-r primality testing algorithm
    for (uint64_t i = 1; i < iters; ++i) {
        //uint64_t a = (uint64_t) (rand() % ( n - 4 )) + 2;
        mpz_urandomm(a, state, n_temp);
        mpz_sub_ui(temp, n_temp, 3);
        mpz_mod(a, a, temp);
        mpz_add_ui(a, a, 2);

        //uint64_t y = pow_mod(a, s, n);
        pow_mod(y, a, r, n_temp);

        //if( (y != 1) && (y != n - 1))
        if ((mpz_cmp_ui(y, 1) != 0) && (mpz_cmp(y, n_minus_1) != 0)) {
            mpz_set_ui(j, 1);

            //while ((j <= s - 1) && y != n - 1)
            while ((mpz_cmp(j, s_minus_1) <= 0) && (mpz_cmp(y, n_minus_1) != 0)) {
                //y = pow_mod(y, 2, n);
                pow_mod(y, y, two, n_temp);

                //if (y == 1)
                if (mpz_cmp_ui(y, 1) == 0) {
                    mpz_clears(a, x, temp, y, n_minus_1, j, s_minus_1, two, n_temp, r, NULL);
                    return false;
                }

                //j = j + 1;
                mpz_add_ui(j, j, 1);
            }

            //if (y != n - 1)
            if (mpz_cmp(y, n_minus_1) != 0) {
                mpz_clears(a, x, temp, y, n_minus_1, j, s_minus_1, two, n_temp, r, NULL);
                return false;
            }
        }
    }
    mpz_clears(a, x, temp, y, n_minus_1, j, s_minus_1, two, n_temp, r, NULL);
    return true;
}

//Generate a random prime number
//Returns void
//
//p: the random prime generated
//bit: number of bits the prime number should be
//iters: how many iterations of m-r primality testing is to be used
void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    mpz_t temp; //creating temp var so that I don't override input
    mpz_init(temp);

    //keep generating random numbers until we find a
    //prime number that is roughly nbits long
    do {
        mpz_urandomb(temp, state, bits);
    } while (!is_prime(temp, iters));

    mpz_set(p, temp);
    mpz_clear(temp);
    return;
}

//Determine the gcd of a and b
//Returns void
//
//g: the common divisor found
//a,b: the two numbers to find the gcd for
//NOTE: algorithm psuedocode was provided to us
void gcd(mpz_t g, mpz_t a, mpz_t b) {
    //uint64_t t = 0;
    mpz_t t, a_temp, b_temp;
    mpz_inits(t, a_temp, b_temp, NULL);
    mpz_set_ui(t, 0);

    mpz_set(a_temp, a);
    mpz_set(b_temp, b);

    //while (b !=0)
    while (mpz_cmp_ui(b_temp, 0) != 0) {
        //t = b
        //b = a % b
        //a = t
        mpz_set(t, b_temp);
        mpz_mod(b_temp, a_temp, b_temp);
        mpz_set(a_temp, t);
    }

    mpz_set(g, a_temp); //return a
    mpz_clears(t, a_temp, b_temp, NULL);
    return;
}

//Calculate the modular inverse of a and n (a^-n mod n)
//Returns a void
//
//o: the mod-inverse result of a , n
//a: number to inverse
//n: modulus
//NOTE: algorithm pseudocode was provided to us in the assignment doc
void mod_inverse(mpz_t o, mpz_t a, mpz_t n) {
    mpz_t r, r_prime, t, t_prime, q, temp, mul_temp, a_temp, n_temp;
    mpz_inits(r, r_prime, t, t_prime, q, temp, mul_temp, a_temp, n_temp, NULL);

    mpz_set(a_temp, a);
    mpz_set(n_temp, n);

    //(r,r_prime)←(n,a)
    mpz_set(r, n_temp);
    mpz_set(r_prime, a_temp);

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
        mpz_set_ui(o, 0);
        mpz_clears(r, r_prime, t, t_prime, q, temp, mul_temp, n_temp, a_temp, NULL);
        return;
    }

    //if t < 0
    if (mpz_cmp_ui(t, 0) < 0) {
        //t←t+n
        mpz_add(t, t, n_temp);
    }

    //return t
    mpz_set(o, t);

    mpz_clears(r, r_prime, t, t_prime, q, temp, mul_temp, n_temp, a_temp, NULL);
    return;
}
