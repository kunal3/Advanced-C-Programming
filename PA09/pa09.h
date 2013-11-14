#ifndef PA09_H
#define PA09_H
#include <stdio.h>

typedef struct _huffnode {
    int value; 
    struct _huffnode * left;
    struct _huffnode * right;
} HuffNode;

typedef struct _stack {
    struct _stack * next;
    HuffNode * node;
} Stack;

HuffNode * Huffman_bit(FILE * fptr);
HuffNode * Huffman_char(FILE * fptr);
Stack * Stack_create(HuffNode * huff);
Stack * Stack_push(Stack *st, HuffNode * huff);
Stack * Stack_pop(Stack * st);
HuffNode * HuffNode_create(int value);
void Huff_postOrderPrint(HuffNode *tree, FILE * fptr);
void HuffNode_destroy(HuffNode * huff);

#endif
