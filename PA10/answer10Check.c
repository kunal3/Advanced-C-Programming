
#include "pa10.h"
#include "tree.h"
#include "tree.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

void List_destroy(ListNode * list)
{
  if(list != NULL)
    {
      List_destroy(list->next);
      free(list);
    }
}

/**
 * Returns a pointer to a new empty stack.
 */
Stack * Stack_create()
{
  Stack *stack = NULL;
  stack = malloc(sizeof(Stack));
  stack->list = NULL;
  return stack;
}

/**
 * Frees all memory associated with the stack. 
 * Don't forget that you _must_ free the entire contained linked-list.
 * Also, you must safely to _nothing_ if stack == NULL. 
 */
void Stack_destroy(Stack * stack)
{
  if(stack == NULL) return;
  List_destroy(stack->list);
  free(stack);
}


/**
 * Returns TRUE (something other than zero) if the stack is empty.
 */
int Stack_isEmpty(Stack * stack)
{
  // precondition - stack cannot be NULL
  if(stack->list == NULL) return TRUE;
  return FALSE;
}

/**
 * Pop the front 'value' from the stack.
 *
 * More precisely, this function must do two things:
 * (1) Return the value of the head node of the stack's list
 * (2) Remove the head node of the stack's list, freeing it.
 */
int Stack_pop(Stack * stack)
{
  if(stack->list == NULL) return -1;
  int value = stack->list->value;
  ListNode * newList = NULL;
  newList = stack->list->next;
  free(stack->list);
  stack->list = newList;
  return value;
}

/**
 * Push an 'value' onto the front of the stack.
 *
 * More precisely, this function must:
 * (1) Create a new ListNode with 'value' for it's value.
 * (2) Push that new ListNode onto the front of the stack's list.
 */
void Stack_push(Stack * stack, int value)
{
  ListNode * newList = NULL;
  newList = malloc(sizeof(ListNode));
  newList->value = value;
  newList->next = stack->list;
  stack->list = newList;
}

/**
 * Sort 'array' of length 'len' using Donald Knuth's "StackSort"
 *
 * To do this, you must implement the following pseudo-code:
 * (1) Maintain a 'write_index'. This is where you'll write values to
 *     as you sort them. It starts off as zero.
 * (2) Initialize an empty stack
 * (3) For each input value 'x':
 *     (3.a) While the stack is nonempty and 'x' is larger than the 
 *           front 'value' on the stack, pop 'value' and:
 *           (3.a.i) Write 'value' to array[write_index], and 
 *                   increment write_index.
 *     (3.b) Push x onto the stack.
 * (4) While the stack is nonempty, pop the front 'value' and follow
 *     step (3.a.i).
 *
 * The output should be a sorted array if, and only if, the array
 * is stack-sortable. You can find files full of stack-sortable and
 * stack-unsortable arrays in the 'expected' folder.
 */
void stackSort(int * array, int len)
{
  int wIndex = 0;
  int i = 0;
  Stack *stack = NULL;
  stack = Stack_create();
  for(i=0; i<len; i++)
    {
      while(!Stack_isEmpty(stack) && array[i]>stack->list->value)
	array[wIndex++] = Stack_pop(stack);
      Stack_push(stack, array[i]);
    }
  while(!Stack_isEmpty(stack))
    array[wIndex++] = Stack_pop(stack);
}

/**
 * Return TRUE (1) if the 'array' of length 'len' is stack-sortable.
 *
 * To do this you must:
 * (1) If 'len' is less than 3, return TRUE.
 * (2) Find the maximum value in 'array'.
 * (3) Partition array into two parts: left of max, and right of max.
 * (4) The maximum value in left must be smaller than the minimum
 *     value in right. (Otherwise return FALSE.)
 * (5) Return TRUE if both left and right are stack-sortable.
 *
 * The 'expected' directory contains files for all sortable and 
 * unsortable sequences of length len. You must return TRUE for every
 * sequence in the sortable files, and you must return FALSE for every
 * sequence in the unsortable files.
 */

int isSortable(int *array,int bottom, int len)
{
  if ((len-bottom)<3) return TRUE;
  int max = array[bottom];
  int maxL = array[bottom];
  int minR = 0;
  int i = 0;
  int ind = bottom;

  for(i=bottom; i<len; i++)
    if(array[i]>max)
      {
	max = array[i];
	ind = i;
      }

  if(ind==bottom) return isSortable(array, bottom+1, len);
  else
    {
      for(i=bottom; i<ind; i++)
	if(array[i]>maxL)
	  maxL=array[i];
      
      if(ind<len-1)
	minR = array[ind+1];
      else if (array[ind] > maxL) return isSortable(array, bottom, ind);
      else return FALSE;
      
      for(i=ind+1; i<len; i++)
	if(array[i]<minR)
	  minR = array[i];
      
      if(maxL<minR) return (isSortable(array,0,ind) && isSortable(array, ind+1,len));
      else return FALSE;
    }
}

int isStackSortable(int * array, int len)
{
  return isSortable(array,0,len);
}

/**
 * Generates (and prints) all the unique binary tree shapes of size k
 *
 * To do this, you must:
 * (1) Create an array with the elements [0..k-1] inclusive.
 * (2) Find all the permutations of this array.
 * (3) In the base-case of your permute function, you must test if the
 *     permutation is "stack-sortable"
 * (4) If the permutation is "stack-sortable", then build a binary
 *     tree, and print it using the "Tree_printShape(...)" function.
 *
 * Your genShapes() function must NOT produce duplicate tree shapes.
 * The correct outputs for sizes [1..9] are in the 'expected' 
 * directory.
 */

void swap( int *a, int *b)
{
  int x = *a;
  *a = *b;
  *b = x;
}

void permute(int * array, int pos, int len, FILE * fptr)
{
  int i ;
  if(isStackSortable(array, len) && pos==len)
    {
      TreeNode * root = NULL;
      root = Tree_build(array, len);
      Tree_printShapeHelper(root, fptr);
      fprintf(fptr, "\n");
      Tree_destroy(root);
      return;
    }

  for(i=pos; i< len ;i++)
    {
      swap(&array[pos], &array[i]); 
      permute(array, pos+1, len,fptr);
      swap(&array[pos], &array[i]); 
    }
}

void genShapes(int k, FILE * fptr)
{
  int *array = malloc(sizeof(int)*k);
  int i=0;
  for(i=0; i<k; i++)
    array[i]=i;
  permute(array, 0, k, fptr);
  free(array);
}
