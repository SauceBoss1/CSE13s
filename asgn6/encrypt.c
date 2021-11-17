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
//Returns void
//
//Takes in nothing
void help_msg(void) {
    fprintf(stderr, "SYNOPISIS\n"
                    "   Encrypts data using RSA encryption.\n"
                    "   Encrypted data is decrypted by the decrypt program.\n\n"
                    "USAGE\n"
                    "   ./encrypt [-hv] [-i infile] [-o outfile] -n pubkey -d privkey\n\n"
                    "OPTIONS\n"
                    "   -h              Display program help and usage.\n"
                    "   -v              Display verbose program output.\n"
                    "   -i infile       Input file of data to encrypt (default: stdin).\n"
                    "   -o outfile      Output file for encrypted data (default: stdout).\n"
                    "   -n pbfile       Public key file (default: rsa.pub).\n");
}

int main(int argc, char **argv) {
    FILE *infile = stdin; //default option must be stdin
    FILE *outfile = stdout; //default option must be stdout
    FILE *pbfile = fopen("./rsa.pub", "r"); //assume thaat rsa.pub is a local file

    bool verbose = false;
    int opt = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        case 'n': pbfile = fopen(optarg, "r"); break;
        case 'v': verbose = true; break;
        case 'h':
            help_msg();
            exit(1);
            break;
        default:
            infile = stdin;
            outfile = stdout;
            pbfile = fopen("./rsa.pub", "r");
            break;
        }
    }
    
    //If one of our files has an errror when opening, then abrt the program
    if ((infile == NULL) || (outfile == NULL) || (pbfile == NULL)) {
        fprintf(stderr, "Couldn't open one of the files!\n");
        exit(1);
    }

    mpz_t n, e, s, username;
    mpz_inits(n, e, s, username, NULL);
    char user[1024]; //buffer for username
    
    //read in the input public key
    rsa_read_pub(n, e, s, user, pbfile);
        
    //print out stats of public key
    if (verbose) {
        fprintf(stderr, "user = %s\n", user);
        gmp_fprintf(stderr, "s (%d bits) = %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_fprintf(stderr, "n (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_fprintf(stderr, "e (%d bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
    }
    
    //convert the username string to a 62 base mpz_t
    mpz_set_str(username, user, 62);
    
    //make sure the signature is verified
    if (!rsa_verify(username, s, e, n)) {
        fprintf(stderr, "Signature cannot be verified!\n");
        exit(1);
    }
    
    //encrypt the input file
    rsa_encrypt_file(infile, outfile, n, e);

    mpz_clears(n, e, s, username, NULL);
    fclose(infile);
    fclose(outfile);
    fclose(pbfile);
    return 0;
}
