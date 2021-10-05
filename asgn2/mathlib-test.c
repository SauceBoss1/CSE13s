#include <stdio.h>
#include <unistd.h>

#define OPTIONS "pi:"

int main(int argc, char **argv){
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1){
        switch(opt){
            case 'p':
                printf("-p option. \n");
                break;
            case 'i':
                printf("-i option: %s is parameter./n", optarg);
                break;
        }
    }
    return 0;
}
