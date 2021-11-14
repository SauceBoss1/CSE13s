#include "rsa.h"
#include "numtheory.h"
#include "randstate.h"

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    uint64_t p_bits = (random() % ((3 * nbits) / 4)) + (nbits / 4);
    uint64_t q_bits = nbits - p_bits;

    mpz_t p_temp, q_temp, n_temp, e_temp, p_minus_1, q_minus_1,
        coprime; //using temp vars so I don't accidentally overwrite arguments
    mpz_inits(p_temp, q_temp, n_temp, e_temp, p_minus_1, q_minus_1, coprime, NULL);

    //generate random p and q
    make_prime(p_temp, p_bits, iters);
    make_prime(q_temp, q_bits, iters);

    mpz_sub_ui(p_minus_1, p_temp, 1);
    mpz_sub_ui(q_minus_1, q_temp, 1);

    //compute totient
    mpz_mul(n_temp, p_minus_1, q_minus_1);
    //Find a public exponent

    mpz_set_ui(coprime, 0);
    do {
        mpz_urandomb(e_temp, state, nbits);
        gcd(coprime, e_temp, n_temp);
    } while (mpz_cmp_ui(coprime, 1) != 0);

    mpz_set(e, e_temp);
    mpz_set(n, n_temp);
    mpz_set(p, p_temp);
    mpz_set(q, q_temp);

    mpz_clears(p_temp, q_temp, n_temp, e_temp, p_minus_1, q_minus_1, coprime, NULL);

    return;
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n", n);
    gmp_fprintf(pbfile, "%Zx\n", e);
    gmp_fprintf(pbfile, "%Zx\n", s);
    gmp_fprintf(pbfile, "%s\n", username);
    return;
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    mpz_t temp;
    mpz_init(temp);
    for (int i = 0; i < 3; ++i) {
        if (gmp_fscanf(pbfile, "%Zx", temp) > 0) {
            if (i % 3 == 0) {
                mpz_set(n, temp);
            } else if (i % 3 == 1) {
                mpz_set(e, temp);
            } else if (i % 3 == 2) {
                mpz_set(s, temp);
            }
        }
    }
    gmp_fscanf(pbfile, "%s", username);
    mpz_clear(temp);
    return;
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t p_minus_1, q_minus_1, n;
    mpz_inits(p_minus_1, q_minus_1, n, NULL);

    mpz_sub_ui(p_minus_1, p, 1);
    mpz_sub_ui(q_minus_1, q, 1);

    mpz_mul(n, p_minus_1, q_minus_1);

    mod_inverse(d, e, n);

    mpz_clears(p_minus_1, q_minus_1, n, NULL);
    return;
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n", n);
    gmp_fprintf(pvfile, "%Zx\n", d);
    return;
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx", n);
    gmp_fscanf(pvfile, "%Zx", d);
    return;
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n){
    mpz_powm(c, m, e, n);
    return;
}

//This function calculates log BASE 2 (n)/
//This pseudocode was provided to us by Prof. Long
static void log2n(mpz_t rop, mpz_t n){
    mpz_t n_temp, c;
    mpz_inits(n_temp, c, NULL);
    
    mpz_abs(n_temp, n);
    mpz_set_ui(c, 0);

    while( mpz_cmp_ui(n_temp, 0) > 0 ){
        mpz_add_ui(c, c, 1);
        mpz_fdiv_q_ui(n_temp, n_temp, 2);
    }

    mpz_sub_ui(c, c, 1);
    mpz_set(rop, c);


    mpz_clears(n_temp, c, NULL);
    return;
}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e){
    mpz_t k;
    mpz_init(k);
    
    //calcuates block size
    log2n(k, n);
    mpz_sub_ui(k, k, 1);
    mpz_fdiv_q_ui(k, k, 8);
    //gmp_fprintf(outfile, "k = %Zd\n", k);
    //dynamically allocate memory for block
    uint8_t *block = (uint8_t *) calloc(mpz_get_ui(k), sizeof(uint8_t));

    fseek(infile, 0L, SEEK_END);
    uint32_t file_size = ftell(infile);
    fseek(infile, 0L, SEEK_SET);

    block[0] = 0xFF;

    mpz_t message;
    mpz_init(message);
    uint32_t j = 0;

    while( j < file_size ){
        uint32_t true_bytes = (uint32_t) fread(block + 1, sizeof(uint8_t), mpz_get_ui(k) - 1, infile);
        j += true_bytes;
        //fprintf(stderr,"j: %"PRIu32" file_size: %"PRIu32"\n", j, file_size);
        mpz_import(message, (size_t) true_bytes, 1, sizeof(uint8_t), 1, 0, block);
        rsa_encrypt(message, message, e, n);
        gmp_fprintf(outfile,"%Zx\n", message);
    }

    mpz_clears(k, message, NULL);
    free(block);
    block = NULL;

    return;
}

int main(void) {
    randstate_init(2021);
    mpz_t p, q, n, e, d;
    mpz_inits(p, q, n, e, d, NULL);

    rsa_make_pub(p, q, n, e, 128, 10000);
    rsa_make_priv(d, e, p, q);
    


    rsa_encrypt_file(stdin, stdout, n, e);
    //rsa_write_priv(n, d, stdout);
    //rsa_read_priv(n, d, stdin);
    //gmp_printf("n: %Zd d: %Zd\n", n, d);
    //char username[1024];

    //gmp_printf("p: %Zd\nq: %Zd\nn: %Zd\ne: %Zd\nd: %Zd\n", p, q, n, e, d);

    //rsa_write_pub(n, e, p, "dtercian", stdout);

    //rsa_read_pub(n, e, p, username, stdin);

    //gmp_printf("n: %Zd\ne: %Zd\ns: %Zd\nuser: %s\n", n, e, p, username);

    //rsa_write_pub(n, e, p, username, stdout);

    mpz_clears(p, q, n, e, d, NULL);
    randstate_clear();
    return 0;
}
