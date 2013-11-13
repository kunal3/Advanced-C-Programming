#include "pa09.h"
#include <stdio.h>
#include <stdlib.h>

// run line
// gcc -Wall -Wshadow -g -DMYTEST utility.c && ./a.out

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
      if((onebyte&mask[cmdloc]) == mask[cmdloc]) // command is 1
	{
	  printf(" [1] "); fflush(stdout);

	  x<<=(cmdloc+1);
	  y>>=(7-cmdloc);
	  x=x|y;

	  printByte(x); printf("\n"); fflush(stdout);

	  //HuffNode *a = HuffNode_create(x);
	  //st = Stack_push(st, a);
	}
      else
	{
	  printf(" [0] "); fflush(stdout);
	  do
	    {
	      HuffNode * a = NULL;
	      //a = st->node;
	      //st = Stack_pop(st);
	      if(st == NULL)
		{
		  printf("Terminating condition\n");
		  return a;
		}
	      else
		{
		  if(0) {
		    HuffNode *b = st->node;
		    st = Stack_pop(st);
		    HuffNode * par = malloc(sizeof(HuffNode));
		    par->value = ' '; 
		    par->right = a;
		    par->left = b;
		    st = Stack_push(st, par);
		  }
		}
	      cmdloc=(cmdloc+1)%8;
	    }while((onebyte&mask[cmdloc])==0);
	  fseek(fptr, -1, SEEK_CUR);
	  cmdloc--;
	} // end of command = 0

      cmdloc=(cmdloc+1)%8;
    } // end of while
  return NULL;
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
  return NULL;
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

#ifdef MYTEST
// gcc -Wall -Wshadow -g -DMYTEST utility.c && ./a.out
int main(int argc, char * * argv)
{
  const char * filename = "/tmp/binary";
  {
    /*
 [1] 0001-1110 
 [1] 1101-1011 
 [1] 1111-1110 
 [1] 0111-1101 
 [1] 1110-0000 
 [1] 1111-0100 
 [1] 0000-1001 
 [1] 1000-1111 
    */
    FILE * fp = fopen(filename, "wb");
    unsigned char bits[] = { 0b10001111, 
			     0b01110110, 
			     0b11111111, 
			     0b11010111,
			     0b11011111,
			     0b00000111,
			     0b11010010,
			     0b00010011,
			     0b10001111, 

			     0b01110110, 
			     0b11111111, 
			     0b11010111,
			     0b11011111,
			     0b00000111,
			     0b11010010,
			     0b00010011
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

