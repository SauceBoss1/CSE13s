#include "code.h"
#include "defines.h"

#include <stdbool.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>


Code code_init(void){
    Code c;
    c.top = 0;
    for (uint8_t i = 0; i < MAX_CODE_SIZE; ++i){
        c.bits[i]= 0;
    }

    return c;
}

uint32_t code_size(Code *c){
    return c->top;
}

bool code_empty(Code *c){
    if (c->top == 0){
        return true;
    }
    return false;
}

bool code_full(Code *c){
    if (c->top == MAX_CODE_SIZE){
        return true;
    }
    return false;
}

bool code_set_bit(Code *c, uint32_t i){
    if (i > ALPHABET){
        return false;
    }

    c->bits[i / 8] |= (0x1 << i % 8);
    return true;
}

bool code_clr_bit(Code *c, uint32_t i){
    if (i > ALPHABET){
        return false;
    }

    c->bits[i / 8] &= ~(0x1 << i % 8);
    return true;
}

bool code_get_bit(Code *c, uint32_t i){
    if (i > ALPHABET){
        return false;
    }
    return (c->bits[i / 8] >> 2 % 8) & 0x1;
}

bool code_push_bit(Code *c, uint8_t bit){
    if (c->top >= MAX_CODE_SIZE){
        return false;
    }

    c->bits[i / 8] |= (bit << i % 8);
    c->top++;
    return true;
}

bool code_pop_bit(Code *c, uint8_t *bit){
    if (code_empty(c)){
        return false;
    }

    *bit = code_get_bit(c->top);
    c->top--;
    return true;
}

void code_print(Code *c){
    printf("[ ");
    for (uint8_t i = 0; i < MAX_CODE_SIZE; ++i){
        printf("%" PRIu8 "  ", c->bits[i]);
    }
    printf("]\n");
}

int main(void){
    Code c;
    c = code_init();
    
    code_push_bit(&c, 1);
    
    code_print(&c);
    return 0;
}
