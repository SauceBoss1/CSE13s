# Assignment 6: Public Key Cryptography

#### By: Derfel Terciano

## Synopsis

This is a program that can securely encrypt and decrpyt files using Public Key Cryptography. In this assignment, we will specifically be using the RSA encryption algorithm in order to securely encrypt and decrypt files. 

In order for the RSA encryption algorithm to be effective, we must generate a pair of keys: a public key and a private key.

In order to encrypt a file, we would use the public key in order to encrypt the file. In order to decrypt a file, we would need to use the corresponding private key in order to decipher the encrypted file. Once decipher, the result would be the original message given to the encryption algorithm.

NOTE: In order for this algorithm to be secure, the private key must be kept secret at all times.

## Building the program

Once all the files are in a local directory, type `make` in the terminal and the following binaries should be built:

- encrypt
- decrypt
- keygen

Once you are done with using the executables, just type `make clean` in the terminal in order to delete all the executables and the object files the compiler  built.

## How to run the program

Once `keygen`, `encrypt`, and `decrypt` have been built, you can type in the following in order to display the help message:

- `./<executable> -h`

### Encrypt:

The following list is the command line options for `encrypt`:

- -i: specifies the input file to encrypt (default: stdin).
- -o: specifies the output file to encrypt (default: stdout).
- -n: specifies the file containing the public key (default: rsa.pub).
- -v: enables verbose output.
- -h: displays program synopsis and usage.

### Decrypt:
The following list is the command line options for `decrypt`:

- -i: specifies the input file to decrypt (default: stdin).
- -o: specifies the output file to decrypt (default: stdout).
- -n: specifies the file containing the private key (default: rsa.priv).
- -v: enables verbose output.
- -h: displays program synopsis and usage.

### Keygen:
The following list is the command line options for `keygen`:

- -b: specifies the minimum bits needed for the public modulus n.
- -i: specifies the number of Miller-Rabin iterations for testing primes (default: 50).
- -n pbfile: specifies the public key file (default: rsa.pub).
- -d pvfile: specifies the private key file (default: rsa.priv).
- -s: specifies the random seed for the random state initialization (default: the seconds since the UNIX epoch, given by time(NULL)).
- -v: enables verbose output.
- -h: displays program synopsis and usage.

## Errors/Problems

So far, there are no issues with the program. 
