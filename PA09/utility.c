#include "pa09.h"
#include <stdio.h>
#include <stdlib.h>

HuffNode * Huffman_char(FILE * fptr)
{
  int command=fgetc(fptr);
  int character=0;
  Stack * st = NULL; 

  while(!feof(fptr)) // not end of tree THIS IS WRONG
    {
      if(command == 49) // command is 1
	{
	  character = fgetc(fptr);
	  HuffNode *a = HuffNode_create(character);
	  st = Stack_push(st, a);
	}
      else if(command == 48)
	{
	  HuffNode *a = st->node;
	  st = Stack_pop(st);
	  if(st == NULL)
	    {
	      return a;
	    }
	  else
	    {
	      HuffNode *b = st->node;
	      st = Stack_pop(st);
	      HuffNode * par = malloc(sizeof(HuffNode));
	      par->value = ' '; // doesn't matter
	      par->right = a;
	      par->left = b;
	      st = Stack_push(st, par);
	    }
	}
      command = fgetc(fptr);
    }
  return st->node;
}

Stack * Stack_create(HuffNode * huff)
{
  Stack * st;
  st = malloc(sizeof(Stack));
  st -> node = huff;
  st -> next = NULL;
  return st;
}

Stack * Stack_push(Stack *st, HuffNode * huff)
{
  Stack * newNode = Stack_create(huff);
  newNode->next = st;
  newNode->node = huff;
  return newNode;
}

Stack * Stack_pop(Stack * st)
{
  if (st == NULL) return NULL;
  Stack * b = st -> next;
  free (st);
  return b;
}

HuffNode * HuffNode_create(int value)
{
  HuffNode * huff = malloc(sizeof(HuffNode));
  huff -> value = value;
  huff -> left = NULL;
  huff -> right = NULL;
  return huff;
}

void Huff_postOrderPrint(HuffNode *tree, FILE * fptr)
{
  if (tree == NULL) return;
  fprintf(fptr, "Left\n");
  Huff_postOrderPrint(tree->left, fptr);
  fprintf(fptr, "Back\n");
  fprintf(fptr, "Right\n");
  Huff_postOrderPrint(tree->right, fptr);
  fprintf(fptr, "Back\n");
  
  if (tree->left == NULL && tree->right == NULL) 
    fprintf(fptr, "Leaf: %c\n", tree->value);
}

void HuffNode_destroy(HuffNode * huff)
{
  if(huff!=NULL)
    {
      HuffNode_destroy(huff->left);      
      HuffNode_destroy(huff->right);
      free(huff);
    }
}

int ifLeaf(HuffNode * huff)
{
  if(huff == NULL) return 1;
  if(huff->left != NULL) return 0;
  if(huff->right != NULL) return 0;
  return 1;
}

/* while(!isLeaf) */
/*   { */
/*     read one bit */
/*     if(bit == 0) go left */
/*     if(bit == 1) go right */
/*   } */
/* print the value and return to root */
