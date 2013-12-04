#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include "pa12.h"

#define SUCCESS 0
#define FAILURE -1

// function definition in pa12.h :
// int subsetSum(int * intset, int length, int targetSumValue, int numThread);


/* typedef struct{ */

/* }Task; */

/*
* Write a parallel C program that returns the answer for the following problem:
* Given a nonempty set S, with elements {a1, a2, a3, ...}, and a integer N, 
* find the number of nonempty subsets of S, such that the sum of all elements 
* in this subset equals to N.
*
* Arguments:
*	intset - pointer to an array of a integer set
*	length - size (length) of the integer set
*	N - target sum value
*	numThread - number of threads 
* Return value:
*	numOfSolutions - Number of nonempty subsets in which the subsetSum value 
*	matches with N. This variable should be protected as the critical 
*	sections by using mutex objects.
*
* Hint: The total number of possible subsets is (2^(length)-1). You may use
* 	math library function 'pow()' to assign the index for each thread.
* 	pthread.h and math.h are already included in this file.
*/

void generateBinary(int l, int * subsets)
{
  int i = 0;
  int counter = 0;
  for(i = 0; i < l; i++)
    for(counter = 31; counter>=0; counter--)
      {
	if(i>>counter & 1) subsets[i] = subsets[i]*10 + 1;
	else subsets[i] *= 10;
      }
}

void generateSubs(int l, int * subsets, int numSubs)
{
  int i;
  // for(i = 0; i < numSubs; i++)
  // {
  //    if(subsets[i]%2 == 1) // and then chop off last digit and so on
  //}
}

int subsetSum(int * intset, int length, int N, int numThread)
{
  int numSubs = pow(2,length);
  int * subsets = malloc(sizeof(int) * numSubs-1);
  
  generateBinary(numSubs, subsets);
  
  int i = 0;
  printf("Printing subsets:\n");
  for(i = 0; i<numSubs; i++)
    printf("%d\n", subsets[i]);
  
  generateSubs(numSubs, subsets, numSubs);
  
  
  free(subsets);
  return 1;
}

// clear && gcc -lm -Wall -Wshadow -g subsetSum.c && ./a.out

int main(int argc, char ** argv)
{
  int length = 3;
  int * array = malloc(sizeof(int) * length);
  array[0] = -2;
  array[1] = 1;
  array[2] = 2;

  printf("\nnumSets: %d\n\n", subsetSum(array,length,0,0));
  
  free(array);

  return 0;
}
