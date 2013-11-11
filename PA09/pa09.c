#include <stdio.h>
#include <stdlib.h>
#include "pa09.h"

int main(int argc, char** argv)
{
  if(argc<2)
    {
      printf("usage: ./pa09 <input file> <output file>\n");
      return EXIT_FAILURE;
    }
  FILE * fptr = NULL;
  fptr = fopen(argv[1], "r");
  if (fptr == NULL)
    {
      printf("File error!\n");
      return EXIT_FAILURE;
    }
  
  HuffNode * array = NULL;
  array = Huffman_char(fptr);
  fclose(fptr);
  
  fptr = fopen(argv[2], "w");
  if (fptr == NULL)
    {
      printf("output file error\n");
      return EXIT_FAILURE;
    }

  Huff_postOrderPrint(array, fptr);

  fclose(fptr);
  HuffNode_destroy(array);

  return EXIT_SUCCESS;
}
