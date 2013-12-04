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

int generateSubs(int * intset, int l, int N, int * subsets, int numSubs)
{
  int i;
  int j;
  // we may need individual to do it recursively
  //int * indi = malloc(sizeof(int) * l); // individual
  int sum = 0;
  int Nmatch = 0;
  int check = 1;

  // at this we have 3 arrays-
  // subsets contains subsets in binary form - 
  // intset contains all numbers in decimal form in the set
  // individual contains each subset, changes itself numSub times
  // list: 92 87 23 89 126 023 17 -2 812 -23  corresponds
  // binr:  1  0  1  0   1   1  1  1   1   0 BACKWARDS
  
  for(i = 0; i < numSubs; i++)
    {
      check = 1;
      printf("\nsubset[%d]:",i);
      for(j = 0; j < l; j++)
	{
	  if(j == 0 && subsets[i] == 0)
	    check = 0;
	  if(subsets[i]%2 == 1)
	    {
	      sum+= intset[j];
	      printf(" %d",intset[j]);
	    }
	  subsets[i]/=10;
        }
      printf(",      sum = %d",sum);
      if(sum == N && check) Nmatch++;
      sum = 0;
    }

  return Nmatch;
}

int subsetSum(int * intset, int length, int N, int numThread)
{
  int numSubs = pow(2,length);
  int * subsets = malloc(sizeof(int) * numSubs-1);
  
  int i = 0;
  printf("intset: ");
  for(i = 0; i < length; i++)
    {
      printf("%d ", intset[i]);
    }
  printf("\nSum: %d",N);
  
  generateBinary(numSubs, subsets);  
  numSubs = generateSubs(intset, length, N, subsets, numSubs);
  
  free(subsets);
  return numSubs;
}

// clear && gcc -lm -Wall -Wshadow -g subsetSum.c && ./a.out

int main(int argc, char ** argv)
{
  int length = 16;
  int * array = malloc(sizeof(int) * length);
  array[0] = 81;
  array[1] = -29;
  array[2] = -16;
  array[3] = -66;  
  array[4] = -80;
  array[5] = 8;
  array[6] = 9;
  array[7] = 63;
  array[8] = -30;
  array[9] = 29;
  array[10] = 32;
  array[11] = 28;
  array[12] = 80;
  array[13] = 44;
  array[14] = -86;
  array[15] = 78;

  // subset takes intset, length, N, numThread
  printf("\nnumSets: %d\n\n", subsetSum(array,length,0,0));
  
  free(array);

  return 0;
}
