#include <stdio.h>
#include <stdlib.h>
#include "pa09.h"

int main(int argc, char** argv)
{
  if(argc!=3)
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
  
  SparseNode * array = NULL;
  array = Huffman(argv[1]);
  
  fclose(fptr);
  
  fptr = fopen(argv[2], "w");
  if (fptr == NULL)
    {
      printf("output file error\n");
      return EXIT_FAILURE;
    }

  // code

  SparseArray_destroy(array);
  fclose(fptr);
  return EXIT_SUCCESS;
}
