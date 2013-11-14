#include "pa09.h"
#include <stdio.h>
#include <stdlib.h>

// function to create a Huffman tree for binary input and return the head
HuffNode * Huffman_bit(FILE * fptr)
{
  // initialize variables
  unsigned char onebyte = fgetc(fptr);  
  unsigned char x = onebyte;
  unsigned char y = 0;
  int command = 0; 
  int cmdloc = -1;
  unsigned char mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
  Stack *st = NULL;

  while(!feof(fptr))
    {
      // update the command location, then get the new command
      cmdloc=(cmdloc+1)%8;
      command = (((onebyte&mask[cmdloc])==mask[cmdloc])? 1:0);

      if(command) // if command = 1
	{
	  // get the next byte but move the file cursor back for future use.
	  y = fgetc(fptr);     
	  fseek(fptr, -1, SEEK_CUR);
	  
	  // add right part of x and left part of y
	  x<<=(cmdloc+1);
	  y>>=(7-cmdloc);
	  x=x|y;

	  // create a HuffNode with the new x and push it on the stack
	  HuffNode *a = HuffNode_create(x);
	  st = Stack_push(st, a);

	  // get the next byte, get next 2 bytes if command location is 7
	  onebyte = fgetc(fptr);
	  if(cmdloc==7)
	    onebyte = fgetc(fptr);
	  x = onebyte;
	}
      else // if command = 0
	{
	  // get the first HuffNode and pop the stack node
	  HuffNode * a = NULL;
	  a = st->node;
	  st = Stack_pop(st);
	  if(st == NULL) return a;
	  else
	    {
	      // if the the 0 node is a parent of two nodes, create a parent
	      // and push it on the stack
	      HuffNode *b = st->node;
	      st = Stack_pop(st);
	      HuffNode * par = malloc(sizeof(HuffNode));
	      par->value = ' '; 
	      par->right = a;
	      par->left = b;
	      st = Stack_push(st, par);
	    }
	  // special case if a 0 command is at the end of a byte
	  if(cmdloc == 7)
	    {
	      onebyte = fgetc(fptr);
	      x = onebyte;
	    }
	}
    }
  return NULL;
}

// function to create a Huffman tree for character input and return the head
HuffNode * Huffman_char(FILE * fptr)
{
  // initialize variables
  int command=fgetc(fptr);
  int character=0;
  Stack * st = NULL; 

  while(!feof(fptr)) // while not end of tree 
    {
      if(command == 49) // if command is 1
	{
	  // get the character and push it on the stack
	  character = fgetc(fptr);
	  HuffNode *a = HuffNode_create(character);
	  st = Stack_push(st, a);
	}
      else if(command == 48) // if command is 0
	{
	  // pop the topmost node after getting it's HuffNode
	  HuffNode *a = st->node;
	  st = Stack_pop(st);
	  if(st == NULL) return a;
	  else
	    {
	      // if the the 0 node is a parent of two nodes, create a parent
	      // and push it on the stack
	      HuffNode *b = st->node;
	      st = Stack_pop(st);
	      HuffNode * par = malloc(sizeof(HuffNode));
	      par->value = ' ';
	      par->right = a;
	      par->left = b;
	      st = Stack_push(st, par);
	    }
	}
      // get the next command
      command = fgetc(fptr);
    }
  return NULL;
}

Stack * Stack_create(HuffNode * huff)
{
  // creates a Stack which references the given HuffNode and returns the new head
  Stack * st;
  st = malloc(sizeof(Stack));
  st -> node = huff;
  st -> next = NULL;
  return st;
}

Stack * Stack_push(Stack *st, HuffNode * huff)
{
  // pushes the given HuffNode on the given Stack and returns the new head
  Stack * newNode = Stack_create(huff);
  newNode->next = st;
  newNode->node = huff;
  return newNode;
}

Stack * Stack_pop(Stack * st)
{
  // Pops the topmost element on the stack and returns the next element
  if (st == NULL) return NULL;
  Stack * b = st -> next;
  free (st);
  return b;
}

HuffNode * HuffNode_create(int value)
{
  // creates a HuffNode with the given value and returns its pointer
  HuffNode * huff = malloc(sizeof(HuffNode));
  huff -> value = value;
  huff -> left = NULL;
  huff -> right = NULL;
  return huff;
}

void Huff_postOrderPrint(HuffNode *tree, FILE * fptr)
{
  // prints the HuffNode in POST-ORDER to the specified file pointer
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
  // destroys the given HuffNode and frees memory
  if(huff!=NULL)
    {
      HuffNode_destroy(huff->left);      
      HuffNode_destroy(huff->right);
      free(huff);
    }
}

// FOLLOWED IS DEBUGGING CODE WRITTEN BY TA AARON MICHEUX

/*
void printByte(unsigned char b)
{
  int i;
  for(i = 0; i < 8; ++i) {
    printf("%d", (int)((b >> (7-i)) & 1));
    if(i == 3)
      printf("-");
  }
  printf(" ");
}

#ifdef MYTEST
// gcc -Wall -Wshadow -g -DMYTEST utility.c && ./a.out
int main(int argc, char * * argv)
{
  const char * filename = "/tmp/binary";
  {
    FILE * fp = fopen(filename, "wb");
    unsigned char bits[] = { 0b10001111, 
			     0b01110110, 
			     0b11111111, 
			     0b11010111,
			     0b11011111,
			     0b00000111,
			     0b11010010,
			     0b00010011,

			     0b11111111,
			     0b01010101,
			     0b11101010,

			     0b10001111, 
			     0b01110110, 
			     0b11111111, 
			     0b11010111,
			     0b11011111,
			     0b00000111,
			     0b11010010,
			     0b00010011,
			     0b00000000,

			     0b00000000,
			     0b00000000
    };
    int len = sizeof(bits) / sizeof(unsigned char);
    int i;
    for(i = 0; i < len; ++i)
      fwrite(&bits[i], 1, 1, fp);
    fclose(fp);
  }

  FILE * fp = fopen(filename, "rb");
  Huffman_bit(fp);
  fclose(fp);

  return 0;
}

#endif

*/
