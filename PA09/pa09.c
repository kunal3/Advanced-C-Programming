#include <string.h>
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

  // checks if input is binary or character
  if(strstr(argv[1], "_ch")!=NULL)
    array = Huffman_char(fptr);
  else if(strstr(argv[1], "_bit")!=NULL)
    array = Huffman_bit(fptr);

  fclose(fptr);
  
  // opens the file to write output
  fptr = fopen(argv[2], "w");
  if (fptr == NULL)
    {
      printf("output file error\n");
      return EXIT_FAILURE;
    }

  // prints the array in post order to the file
  Huff_postOrderPrint(array, fptr);

  fclose(fptr);
  // frees memory
  HuffNode_destroy(array);

  return EXIT_SUCCESS;
}
