# Assignment 7: The Great Firewall of Santa Cruz
### By Derfel Terciano

## Synopsis

This programs filters out words based on the newspeak and the badspeak file. If a the program detects that the stdin input has a word in either or both newspeak and badspeak files, then either a badspeak, mixspeak, or a goodspeak message will be produced from the program. Following the message, the list of words used with their possible translations are produced. If the word has no translation, then the word is a banned badspeak word.

## Building the program

Once all the files are in the local directoy, type `make` into the terminal and the banhammer binary should be built.

Once you are done with the program type `make clean` in order to remove all object files and executables.

## How to run the prgram

Once `banhammer` has been built, you can use the executable in the following manner:

- `./banhammer -arg1 -arg2...`

The program takes an input from `stdin` therefore, you can use `<` in order to give it a text file or use the terminal itself to type in your input.

If you are using the terminal to type in your input, remember to use `CTRL + D` in order to signal `EOF` to stdin and the program.

The program also uses the following optional command line options:

- -h prints out the program usage.
- -t size specifies that the hash table will have size entries (the default will be 2^16).
- -f size specifies that the Bloom filter will have size entries (the default will be 220).
- -s will enable the printing of statistics to stdout. 

## Errors
So far, there are no issues with the program.
