#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include "pa12.h"

#define SUCCESS 0
#define FAILURE -1

typedef struct{
  int * set;
  int len;
  int N;
  int start;
  int end;
  int * counter;
}Task;

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

int sumOf(int * set, int len, int mask)
{
  // cant take len > 30
  int ret = 0;
  int i;
  for(i = 0; i < len; i++)
    if((mask>>i)%2)
      ret += set[i];
  return ret;
}

int subsetSumEq(int * set, int len, int N, int start, int end)
{
  int count = 0;
  int i = 0;
  for(i = start; i < end; ++i)
      if(sumOf(set, len, i) == N)
	  count++;
  return count;
}

// so this will be passed to every thread, and this will call subsetSumEq
// because threads require this function signature
void * subsetSumTask (void * tasks)
{
  Task * task = (Task *)tasks;
  int count = subsetSumEq(task->set, task->len, task->N, task->start, task->end);
  task->counter = count;
  return;
}

Task * createTasks(int * set, int len, int numThread, int N)
{
  Task * tasks[numThread];
  int division = len/numThread;
  int i = 0;
  for(i = 0; i < numThread; i++)
    {
      tasks[i]->set = set;
      tasks[i]->len = division;
      tasks[i]->N = N;
      tasks[i]->start = i*division;
      tasks[i]->end = i*division + division;
    }
  // last set is a special case
  --i;
  tasks[i]->len = len - (i*division);
  tasks[i]->end = len;
  return tasks;
}

int subsetSum(int * intset, int length, int N, int numThread)
{
  int answer = 0;
  int thread_ret = 0;
 
  // create Tasks
  Task * tasks = createTasks(intset, length, numThread, N);

  // create threads
  int i;
  pthread_t threads[numThread];
  for(i = 0; i < numThread ; i++)
    thread_ret = pthread_create(&threads[i], NULL, subsetSumTask, (void*)&tasks[i]);
  if(thread_ret) printf("Thread create failed.\n");

  // run threads
  
  // join threads
  for(i = 0; i < numThread; i++)
    pthread_join(threads[i], NULL);

  // sum up results
  for(i = 0; i < numThread; i++)
    answer += threads[i];

  // free memory

  // return sum
  return answer;
}

// clear && gcc -lm -Wall -Wshadow -g subsetSum.c && ./a.out

int main(int argc, char ** argv)
{
  int intset[] = {1,2,3,4,5};
  int length = sizeof(intset)/sizeof(int);
  int N = 0;
  int numThread = 5;
  printf("\nanswer = %d\n",subsetSum(intset, length, N, numThread));
  
  return EXIT_SUCCESS;
}



// ====================== OLD CODE =====================================
/* void generateBinary(int l, int * subsets) */
/* { */
/*   int i = 0; */
/*   int counter = 0; */
/*   for(i = 0; i < l; i++) */
/*     for(counter = 31; counter>=00; counter--) */
/*       if(i>>counter & 1) subsets[i] = subsets[i]*10 + 1; */
/*       else subsets[i] *= 10; */
/* } */

/* int generateSubs(int * intset, int l, int N, int * subsets, int numSubs) */
/* { */
/*   int i; */
/*   int j; */
/*   int sum = 0; */
/*   int Nmatch = 0; */
/*   int check = 1; */

/*   for(i = 0; i < numSubs; i++) */
/*     { */
/*       check = 1; */
/*       for(j = 0; j < l; j++) */
/* 	{ */
/* 	  if(j == 0 && subsets[i] == 0) */
/* 	    check = 0; */
/* 	  if(subsets[i]%2 == 1) */
/* 	    sum+= intset[j]; */
/* 	  subsets[i]/=10; */
/*         } */
/*       if(sum == N && check) Nmatch++; */
/*       sum = 0; */
/*     } */
/*   return Nmatch; */
/* } */
// =========================== END ===================================
