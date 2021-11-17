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

#define OPTIONS "i:o:n:vh"

//Prints out a help message to stderr
//Returns nothing
//
//Takes in nothing
void help_msg(void) {
    fprintf(stderr, "SYNOPSIS\n"
                    "   Decrypts data using RSA decryption.\n"
                    "   Encrypted data is encrypted by the encrypt program.\n\n"
                    "USAGE\n"
                    "   ./decrypt [-hv] [-i infile] [-o outfile] -n privkey\n\n"
                    "OPTIONS\n"
                    "   -h              Display program help and usage.\n"
                    "   -v              Display verbose program output.\n"
                    "   -i infile       Input file of data to decrypt (default: stdin).\n"
                    "   -o outfile      Output file for decrypted data (default: stdout).\n"
                    "   -n pvfile       Private key file (default: rsa.priv).\n");
}

int main(int argc, char **argv) {
    FILE *infile = stdin; //default option is stdin
    FILE *outfile = stdout; //default option is stdout
    FILE *pvfile = fopen("./rsa.priv", "r"); //assume that rsa.priv is a local file

    bool verbose = false;
    int opt = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        case 'n': pvfile = fopen(optarg, "r"); break;
        case 'v': verbose = true; break;
        case 'h':
            help_msg();
            exit(1);
            break;
        default:
            infile = stdin;
            outfile = stdout;
            pvfile = fopen("./rsa.priv", "r");
            break;
        }
    }

    //if one of the 3 files has an error opening, then abort the program
    if ((infile == NULL) || (outfile == NULL) || (pvfile == NULL)) {
        fprintf(stderr, "Couldn't open a file!\n");
        exit(1);
    }

    mpz_t n, d;
    mpz_inits(n, d, NULL);

    //read in the private key
    rsa_read_priv(n, d, pvfile);

    //print out the stats of the private key
    if (verbose) {
        gmp_fprintf(stderr, "n (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_fprintf(stderr, "d (%d bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }

    //decrypt the file to clear text
    rsa_decrypt_file(infile, outfile, n, d);

    mpz_clears(n, d, NULL);
    fclose(infile);
    fclose(outfile);
    fclose(pvfile);
    return 0;
}
