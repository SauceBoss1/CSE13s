# Assignment 5: Huffman Coding
### By Derfel Terciano

## Synopsis

This program uses Huffman Coding to compress files. In this assignment, we have built both a Huffman encoder and a Huffman decoder. The encoder creates a Huffman tree and creates Huffman codes based on that tree. 

## Building the program

Once you have all the files locally, just type ```make` ``in the terminal in order to build both the decode and encode executables.

Once you are done with the program and want to delete the program, just type ```make clean` ``in order to remove all executables and all object files.

## How to run the program 

Once you have either ```decode` ``````or ```````encode` ``just type the following:

````- `````` `./<executable> -h` ``
This will give you all the help flags needed in order for you to run the program.

### Encoding:

The following is the command line options for the ```````````````````encode````````` ``executable:

- -h: Prints out a help message describing the purpose of the program and the command-line op-
tions it accepts, exiting the program afterwards. Refer to the reference program in the resources
repo for an idea of what to print
- -i infile: Specifies the input file to encode using Huffman coding. The default input should be
set as stdin.
- -o outfile: Specifies the output file to write the compressed input to. The default output should
be set as stdout.
- -v: Prints compression statistics to stderr. These statistics include the uncompressed file size,
the compressed file size, and space saving.

### Decoding:
The following is the command line options for the ```decode````````````````` ``program:

- -h: Prints out a help message describing the purpose of the program and the command-line op-
tions it accepts, exiting the program afterwards. Refer to the reference program in the resources
repo for an idea of what to print.
- -i infile: Specifies the input file to decode using Huffman coding. The default input should be
set as stdin.
- -o outfile: Specifies the output file to write the decompressed input to. The default output
should be set as stdout.
- -v: Prints decompression statistics to stderr. These statistics include the compressed file size,
the decompressed file size, and space saving.

##Issues

So far, it seems like the program decodes and encodes correctly, however, the encoder cannot handle files that are 100,000KB in size. If there is a file that is that big, then the encoder will fail to encode it. Overall, the decoder passes the pipeline.

No memory leaks or segmentation faults have been reported.
