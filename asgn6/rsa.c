#include "rsa.h"
#include "numtheory.h"
#include "randstate.h"

#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

//Create 2 large primes that's nbits long, calcuate n, and determine the public exponent
//Returns void
//
//p: big prime 1
//q: big prime 2
//n: public modulus
//e: public exponent
//nbits: bit length of the primes
//iters: number of iterations used for m-r prime testing
void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {

    mpz_t p_temp, q_temp, totient, e_temp, p_minus_1, q_minus_1, coprime,
        n_temp; //using temp vars so I don't accidentally overwrite arguments
    mpz_inits(p_temp, q_temp, totient, e_temp, p_minus_1, q_minus_1, coprime, n_temp, NULL);
    uint64_t p_bits = (random() % (nbits / 2)) + (nbits / 4);
    uint64_t q_bits = nbits - p_bits;

    //generate random p and q
    do {
        make_prime(p_temp, p_bits + 2, iters);
        make_prime(q_temp, q_bits + 2, iters);
    } while ((mpz_sizeinbase(p_temp, 2) + mpz_sizeinbase(q_temp, 2)) < nbits);
    //This loop guarantees that p + q is nbits long
    //Also we add p and q by two in order to compensat for bit loss

    mpz_mul(n_temp, p_temp, q_temp); //n = p * q

    mpz_sub_ui(p_minus_1, p_temp, 1);
    mpz_sub_ui(q_minus_1, q_temp, 1);

    //compute totient
    mpz_mul(totient, p_minus_1, q_minus_1);

    //Find a public exponent
    //The public exponent is a random number that is coprime to the totient
    mpz_set_ui(coprime, 0);
    do {
        mpz_urandomb(e_temp, state, nbits);
        gcd(coprime, e_temp, totient);
    } while (mpz_cmp_ui(coprime, 1) != 0);

    mpz_set(e, e_temp);
    mpz_set(n, n_temp);
    mpz_set(p, p_temp);
    mpz_set(q, q_temp);

    mpz_clears(p_temp, q_temp, totient, e_temp, p_minus_1, q_minus_1, coprime, n_temp, NULL);

    return;
}

//Writes the public keys to pbfile
//Return void
//
//n: public modulus
//e: public exponent
//s: signature
//username[]: system username
//*pbfile: file to print public keys too
void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n", n);
    gmp_fprintf(pbfile, "%Zx\n", e);
    gmp_fprintf(pbfile, "%Zx\n", s);
    gmp_fprintf(pbfile, "%s\n", username);
    return;
}

//Read the public keys and assign it to the corresponding mpz_t
//Returns void
//
//n: public modulus
//e: public exponent
//s: signature
//username[]: system user
//pbfile: file to read
void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    mpz_t temp;
    mpz_init(temp);
    for (int i = 0; i < 3; ++i) { //the first 3 lines are mpz_t variables
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
    gmp_fscanf(pbfile, "%s", username); //get username
    mpz_clear(temp);
    return;
}

//Generate the private keys based on the primes p and q
//Returns void
//
//d: private key
//e: public exponent
//p: large prime 1
//q: large prime 2
void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t p_minus_1, q_minus_1, n;
    mpz_inits(p_minus_1, q_minus_1, n, NULL);

    mpz_sub_ui(p_minus_1, p, 1);
    mpz_sub_ui(q_minus_1, q, 1);

    mpz_mul(n, p_minus_1, q_minus_1); //Calcuate Totient

    mod_inverse(d, e, n); //d = e^-1 mod n

    mpz_clears(p_minus_1, q_minus_1, n, NULL);
    return;
}

//Write the private keys to a file
//Return void
//
//n: public modulus
//d: private key
//pvfile: file to write to
void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n", n);
    gmp_fprintf(pvfile, "%Zx\n", d);
    return;
}

//Reads the private key from a file
//Returns void
//
//n: public modulus
//d: private key
//pvfile: file to read from
void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx", n);
    gmp_fscanf(pvfile, "%Zx", d);
    return;
}

//Encrypt a message using the power mod
//Returns void
//
//c: encrypted message
//m: message
//e: public exponent
//n: public modulus
void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
    return;
}

//This function calculates log BASE 2 (n)/
//This pseudocode was provided to us by Prof. Long
static void log2n(mpz_t rop, mpz_t n) {
    mpz_t n_temp, c;
    mpz_inits(n_temp, c, NULL);

    mpz_abs(n_temp, n);
    mpz_set_ui(c, 0);

    while (mpz_cmp_ui(n_temp, 0) > 0) {
        mpz_fdiv_q_ui(n_temp, n_temp, 2);
        mpz_add_ui(c, c, 1);
    }

    mpz_set(rop, c);

    mpz_clears(n_temp, c, NULL);
    return;
}

//Encrypt a given file
//Returns void
//
//infile: file to encrypt
//outfile: file to write encrypted data to
//n: public modulus
//e: public exponent
void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    mpz_t k;
    mpz_init(k);

    //calcuates block size
    log2n(k, n);
    mpz_sub_ui(k, k, 1);
    mpz_fdiv_q_ui(k, k, 8);

    //gmp_fprintf(stderr, "k = %Zd\n", k);
    //dynamically allocate memory for block
    uint8_t *block = (uint8_t *) calloc(mpz_get_ui(k), sizeof(uint8_t));

    //Determine the size of infile
    fseek(infile, 0L, SEEK_END);
    uint32_t file_size = ftell(infile);
    fseek(infile, 0L, SEEK_SET);

    //Pad the first byte of the buffer
    block[0] = 0xFF;

    mpz_t message;
    mpz_init(message);
    uint32_t j = 0; //how many total bytes fread has read already

    //while there are unprocessed bytes in infile
    while (j < file_size) {
        uint32_t true_bytes
            = (uint32_t) fread(block + 1, sizeof(uint8_t), mpz_get_ui(k) - 1, infile);
        j += true_bytes;

        //convert the byts to a mpz_t variabe
        mpz_import(message, true_bytes + 1, 1, sizeof(uint8_t), 1, 0, block);
        rsa_encrypt(message, message, e, n);
        gmp_fprintf(outfile, "%Zx\n", message); //print the encrypted message to the outfile
    }

    mpz_clears(k, message, NULL);
    free(block);
    block = NULL;

    return;
}

//Decrypt a file given an ecrypted message, private key, and public modulus
//Returns void
//
//m: decrypted message
//c: encrypted message
//d: private key
//n: public modulus
void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n); //m = c^d mod n
    return;
}

//Decrypts an encrypted file given a private key and the public modulus
//Returns void
//
//infile: an ecrypted file to decrypt
//outfile: the file to write the decrypted message to
//n: public modulus
//d: private key
void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    mpz_t c, k;
    mpz_inits(c, k, NULL);

    //calculate block size k
    log2n(k, n);
    mpz_sub_ui(k, k, 1);
    mpz_fdiv_q_ui(k, k, 8);

    //dynamically alocate the block
    uint8_t *block = (uint8_t *) calloc(mpz_get_ui(k), sizeof(uint8_t));

    int scanned_bytes = 0;
    size_t j = 0;

    //while there are unscanned bytes in file
    while ((scanned_bytes = gmp_fscanf(infile, "%Zx", c)) != EOF) {

        if (scanned_bytes == 0) { //throw an error when we find a malformed line
            fprintf(stderr, "bad read\n");
            exit(1);
        }

        rsa_decrypt(c, c, d, n);
        //export the decrypted mpz_t to the block
        mpz_export(block, &j, 1, sizeof(uint8_t), 1, 0, c);

        //write out j-1 bytes from the block
        fwrite(&block[1], sizeof(uint8_t), j - 1, outfile);
    }

    mpz_clears(c, k, NULL);
    free(block);
    block = NULL;
    return;
}

//Sign a user name given th private key and the public modulus
//Returns void
//
//s: the final signature
//m: the mpz_t to sign
//d: private key
//n: public modulus
void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
    return;
}

//Verify whether or not the signature is authentic
//Returns true if the signature is authentic, false otherwise
//
//m: the username in mpz_t base 62
//s: signature
//e: public exponent
//n: public modulus
bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t t;
    mpz_init(t);

    pow_mod(t, s, e, n);

    //check if t == m
    if (mpz_cmp(t, m) == 0) {
        mpz_clear(t);
        return true;
    }

    mpz_clear(t);
    return false;
}
