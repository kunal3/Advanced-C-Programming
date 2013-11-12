#include "pa09.h"
#include <stdio.h>
#include <stdlib.h>

HuffNode * Huffman_bit(FILE * fptr)
{
  int cmdloc = 0;
  unsigned char mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
  Stack *st = NULL;
  while(!feof(fptr))
    {
      unsigned char onebyte = fgetc(fptr);
      unsigned char x = onebyte;
      unsigned char y = fgetc(fptr);
      fseek(fptr, -1, SEEK_CUR);
 //     printf("cmdloc = %d\n", cmdloc);
 //     printf("fgetc = %d\n", fgetc(fptr));
 //     fseek(fptr, -1, SEEK_CUR);
      if((onebyte&mask[cmdloc]) == mask[cmdloc]) // command is 1
	{
	//  printf("command = 1-----------------\n");
	//  printf("mask = %d\n", mask[cmdloc]);
	  x<<=(cmdloc+1);
	  y>>=(7-cmdloc);
	  x=x|y;
	//  printf("x = %d\n", x);
	  HuffNode *a = HuffNode_create(x);
	  st = Stack_push(st, a);
	}
      else
	{
	 // printf("command = 0----------------\n");
	  do
	    {
	      //printf("i=%d\n",i);
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
		  par->value = ' '; 
		  par->right = a;
		  par->left = b;
		  st = Stack_push(st, par);
		}
	      fseek(fptr, -1, SEEK_CUR);
	      cmdloc=(cmdloc+1)%8;
	      //printf("mask = %d\n", mask[cmdloc+i]);
	    }while((onebyte&mask[cmdloc])==0);
	  fseek(fptr, -1, SEEK_CUR);
	  cmdloc--;
	  //printf("test fgetc=%d\n",fgetc(fptr));
	  //fseek(fptr, -1, SEEK_CUR);
	} // end of command = 0

      cmdloc=(cmdloc+1)%8;
    } // end of while
}

HuffNode * Huffman_char(FILE * fptr)
{
  int command=fgetc(fptr);
  int character=0;
  Stack * st = NULL; 

  while(!feof(fptr)) // not end of tree 
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
