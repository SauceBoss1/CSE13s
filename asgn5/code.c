#include "code.h"
#include "defines.h"

#include <stdbool.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>

//initializes some codes
Code code_init(void) {
    Code c;
    c.top = 0;
    for (uint8_t i = 0; i < MAX_CODE_SIZE; ++i) {
        c.bits[i] = 0;
    }

    return c;
}

//returns the size of the code
uint32_t code_size(Code *c) {
    return c->top;
}

//Returns true if the codes are empty
bool code_empty(Code *c) {
    if (c->top == 0) {
        return true;
    }
    return false;
}

//Returns true if the code array is full
bool code_full(Code *c) {
    if (c->top == ALPHABET) {
        return true;
    }
    return false;
}

//sets the bit to 1 to the code
//i: the index to set
//
//returns false if the index is out of range
bool code_set_bit(Code *c, uint32_t i) {
    if (i > ALPHABET) {
        return false;
    }

    c->bits[i / 8] |= (0x1 << i % 8);
    return true;
}

//clears the bit at a certain index i
bool code_clr_bit(Code *c, uint32_t i) {
    if (i > ALPHABET) {
        return false;
    }

    c->bits[i / 8] &= ~(0x1 << i % 8);
    return true;
}

//gets a bit from a certain index i
//returns false if the index is out of the range
bool code_get_bit(Code *c, uint32_t i) {
    if (i > ALPHABET) {
        return false;
    }
    return (c->bits[i / 8] >> i % 8) & 0x1;
}

//pushes a bit to the code
//bit: the bit value to push
bool code_push_bit(Code *c, uint8_t bit) {
    if (c->top >= MAX_CODE_SIZE) {
        return false;
    }
    if (bit == 1) {
        code_set_bit(c, c->top);
    } else {
        code_clr_bit(c, c->top);
    }
    c->top++;
    return true;
}

//pops a bit from the code
//returns the bit through pass by reference
bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) {
        return false;
    }

    *bit = code_get_bit(c, c->top - 1);
    c->top--;
    return true;
}

//prints the code array
void code_print(Code *c) {
    //printf("[");

    for (uint32_t i = 0; i < code_size(c); ++i) {
        if ((i + 1) % 8 == 0) {
            printf("\n");
        }
        printf("%" PRIu8, code_get_bit(c, i));
    }
    printf("\n");
}

//////////////////////////////////////////////////
//EXAMPLE USAGE OF CODE BELOW

/*
int main(void) {
    Code c;
    c = code_init();
    code_push_bit(&c, 0);
    code_push_bit(&c, 0);
    code_push_bit(&c, 1);
    code_print(&c);

    uint8_t bit = 0;
    code_pop_bit(&c, &bit);
    code_print(&c);
    printf("bit: %"PRIu8 "\n", bit);
    return 0;
}*/
