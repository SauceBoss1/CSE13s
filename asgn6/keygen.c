#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <gmp.h>

#include "randstate.h"
#include "rsa.h"
#include "numtheory.h"

#define OPTIONS "b:i:n:d:s:vh"

void help_msg(void) {
    fprintf(stderr, "SYNOPSIS\n"
                    "   Generates as RSA public/private key pair.\n\n"
                    "USAGE\n"
                    "   ./keygen [-hv] [-b bits] -n pbfile -d pvfile\n\n"
                    "OPTIONS\n"
                    "   -h              Display program help and usage.\n"
                    "   -v              Display verbose program output.\n"
                    "   -b bits         Minimum bits needed for public key n.\n"
                    "   -i iterations   Miller-Rabin iterations for testing primes (default: 50).\n"
                    "   -n pbfile       Public key file (default: rsa.pub).\n"
                    "   -d pvfile       Private key file (default: rsa.priv).\n"
                    "   -s seed         Random seed for testing.\n");
    return;
}

int main(int argc, char **argv) {
    FILE *pbfile = fopen("./rsa.pub", "w");
    FILE *pvfile = fopen("./rsa.priv", "w");

    int opt = 0;

    uint32_t iters = 50;
    uint32_t def_seed = time(NULL);
    uint64_t nbits = 256;
    bool verbose = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': iters = strtol(optarg, NULL, 10); break;
        case 'n': pbfile = fopen(optarg, "w"); break;
        case 'd': pvfile = fopen(optarg, "w"); break;
        case 's': def_seed = strtol(optarg, NULL, 10); break;
        case 'v': verbose = true; break;
        case 'b': nbits = strtol(optarg, NULL, 10); break;
        case 'h':
            help_msg();
            exit(1);
            break;
        default:
            pbfile = fopen("./rsa.pub", "w");
            pvfile = fopen("./rsa.priv", "w");
            break;
        }
    }

    if ((pvfile == NULL) || (pbfile == NULL)) {
        fprintf(stderr, "Couldn't open file!\n");
        exit(1);
    }

    fchmod(fileno(pvfile), 0600);

    randstate_init(def_seed);

    mpz_t p, q, n, e, d, username;
    mpz_inits(p, q, n, e, d, username, NULL);

    do {
        rsa_make_pub(p, q, n, e, nbits, iters);
    } while (mpz_sizeinbase(n, 2) < nbits);
    rsa_make_priv(d, e, p, q);

    char *user = getenv("USER");
    mpz_set_str(username, user, 62);
    rsa_sign(username, username, d, n);

    rsa_write_pub(n, e, username, user, pbfile);
    rsa_write_priv(n, d, pvfile);

    if (verbose) {
        fprintf(stderr, "user = %s\n", user);
        gmp_fprintf(stderr, "s (%d bits) = %Zd\n", mpz_sizeinbase(username, 2), username);
        gmp_fprintf(stderr, "p (%d bits) = %Zd\n", mpz_sizeinbase(p, 2), p);
        gmp_fprintf(stderr, "q (%d bits) = %Zd\n", mpz_sizeinbase(q, 2), q);
        gmp_fprintf(stderr, "n (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_fprintf(stderr, "e (%d bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
        gmp_fprintf(stderr, "d (%d bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }

    mpz_clears(p, q, n, e, d, username, NULL);
    randstate_clear();
    fclose(pvfile);
    fclose(pbfile);
    return 0;
}
