/*
 * Please fill the functions in this file.
 * You can add additional functions. 
 *
 * Hint: 
 * You can write additonal functions.
 * You can test your functions with your own input file.
 * See details in README or typing command ./pa04 in terminal after make.
 * See output format examples in any of the files in directory expected.
 * 
 * You may create additional arrays if needed.  The maximum size
 * needed is specified by MAXLENGTH in pa04.h.
 */

#include "pa04.h"
#include <stdio.h>
#include <stdlib.h>



/*
 * =================================================================
 * This function prints all partitions of a positive integer value
 * For example, if the value is 3:
 *
 * partitionAll 3
 * = 1 + 1 + 1
 * = 1 + 2
 * = 2 + 1
 * = 3
 */

// declaring partAll and printArr
void partAll(int*, int, int);
void printArr(int*, int);

void partitionAll(int value)
{
  printf("partitionAll %d\n", value);

  // creating arr and allocating memory
  int * arr = malloc(value * sizeof(int));
  partAll(arr, 0, value);
  free(arr); // freeing arr 
}

// all partition helper
void partAll(int * arr, int pos, int val)
{
  // if val reaches 0 or less, print from 0 to pos
  if(val <= 0)
    {
      printArr(arr, pos);
      return;
    }

  // partitions all values
  int i;
  for(i=1; i<=val ; ++i)
    {
      arr[pos]=i;
      partAll(arr, pos+1, val-i);
    }
}

// prints arr from 0 to pos
void printArr(int * arr, int pos)
{
  int i;
  if(pos>0)
    printf("= %d", arr[0]);
  for(i = 1; i < pos; i++)
    printf(" + %d", arr[i]);
  printf("\n");
}


/*
 * =================================================================
 * This function prints the partitions that use increasing values.
 *
 * For example, if value is 5
 * 2 + 3 and
 * 1 + 4 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 3 + 2 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */

// declaring partInc
void partInc(int*,int,int);

void partitionIncreasing(int value)
{
  printf("partitionIncreasing %d\n", value);

  // declaring arr and allocating memory
  int * arr = malloc(value * sizeof(int));
  partInc(arr, 0, value);
  free(arr);   // freeing arr's memory
}

// increasing partitions helper and recursive function
void partInc(int * arr, int pos, int val)
{
  // if val reaches 0 or less, print from 0 to pos
  if(val <= 0)
    {
      printArr(arr, pos);
      return;
    }
  int i;
  for(i=1; i<=val ; ++i)
    {
      // only creates partitions if its the first position
      // or i is greater than the last number in arr
      if(pos==0 || (pos>0 && i>arr[pos-1]))
	{
	  arr[pos]=i;
	  partInc(arr, pos+1, val-i);
	}
    }
}

/*
 * =================================================================
 * This function prints the partitions that use Decreasing values.
 *
 * For example, if value is 5
 * 3 + 2 and
 * 4 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */

// declaring partDecreasing
void partDec(int*,int,int);

void partitionDecreasing(int value)
{
  printf("partitionDecreasing %d\n", value);

  // creating arr and allocating memory
  int * arr = malloc(value * sizeof(int));
  partDec(arr, 0, value);
  free(arr);   // free arr's allocated memory
}

void partDec(int * arr, int pos, int val)
{
  if(val <= 0)
    {
      printArr(arr, pos);
      return;
    }
  int i;
  for(i=1; i<=val ; ++i)
    {
      // creates a partition if pos is 0 or 
      // if i is lesser than the last number in arr
      if(pos==0 || (pos>0 && i<arr[pos-1]))
	{
	  arr[pos]=i;
	  partDec(arr, pos+1, val-i);
	}
    }
}

/*
 * =================================================================
 * This function prints odd number only partitions of a positive integer value
 * For example, if value is 5
 * 1 + 1 + 1 + 1 + 1 and
 * 1 + 3 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 1 + 2 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

// declaring partOdd
void partOdd(int*, int, int);

void partitionOdd(int value)
{
  printf("partitionOdd %d\n", value);

  // allocating arr's memory
  int * arr = malloc(value * sizeof(int));
  partOdd(arr, 0, value);
  free(arr);  // freeing arr's space
}

void partOdd(int * arr, int pos, int val)
{
  if(val <= 0)
    {
      printArr(arr, pos);
      return;
    }
  int i;
  for(i=1; i<=val ; ++i)
    {
      // creates partition only if i is odd
      if(i%2!=0)
	{
	  arr[pos]=i;
	  partOdd(arr, pos+1, val-i);
	}
    }
}


/*
 * =================================================================
 * This function prints even number only partitions of a positive integer value
 * For example, if value is 8
 * 2 + 2 + 2 + 2and
 * 2 + 4 + 2 are valid partitions
 *
 * 8 is a valid partition
 *
 * 2 + 1 + 1 + 2 + 2and
 * 2 + 1 + 2 + 3and
 * 5 + 3 are invalid partitions.
 *
 * if the value is 5, there will be no result generated
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

// declaring partEven
void partEven(int*, int, int);

void partitionEven(int value)
{
  printf("partitionEven %d\n", value);
  
  // creating arr and allocating space
  int * arr = malloc(value * sizeof(int));
  partEven(arr, 0, value);
  free(arr);   // freeing arr
}

void partEven(int * arr, int pos, int val)
{
  if(val <= 0)
    {
      printArr(arr, pos);
      return;
    }
  int i;
  for(i=1; i<=val ; ++i)
    {
      // creates a partition only if i is even
      if(i%2==0)
	{
	  arr[pos]=i;
	  partEven(arr, pos+1, val-i);
	}
    }
}



/*
 * =================================================================
 * This function prints alternate ood and even number partitions of a positive integer value. Each partition starts from and odd number, even number, ood number again, even number again...etc.
 *
 * For example, if value is 6
 * 1 + 2 + 1 + 2 and
 * 3 + 2 + 1 are valid partitions
 *
 * 6 is not a valid partition
 *
 * 2 + 1 + 1 + 2 and
 * 2 + 1 + 3and
 * 5 + 1 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

// declaring partOddAndEven
void partOddAndEven(int*, int, int);

void partitionOddAndEven(int value)
{
  printf("partitionOddAndEven %d\n", value);

  // allocating memory for arr
  int * arr = malloc(value * sizeof(int));
  partOddAndEven(arr, 0, value);
  free(arr);   // freeing arr
}

void partOddAndEven(int * arr, int pos, int val)
{
  if(val <= 0)
    {
      printArr(arr, pos);
      return;
    }
  int i;
  for(i=1; i<=val ; ++i)
    {
      // only creates a partition if the 
      // position is even and i is odd
      // or position is odd and i is even
      if((pos%2 == 0 && i%2 != 0) || (pos%2!=0 && i%2==0))
	{
	  arr[pos]=i;
	  partOddAndEven(arr, pos+1, val-i);
	}
    }
}


/*
 * =================================================================
 * This function prints prime number only partitions of a positive integer value
 * For example, if value is 6
 * 2 + 2 + 2 and
 * 3 + 3 are valid partitions
 *
 * 6 is not a valid partition
 * 
 * 2 + 4 and
 * 1 + 5 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

// declaring partPrime and isPrime
void partPrime(int*,int,int);
int isPrime(int);
  
void partitionPrime(int value)
{
  printf("partitionPrime %d\n", value);

  // creating arr and allocating space
  int * arr = malloc(value * sizeof(int));
  partPrime(arr, 0, value);
  free(arr);    // freeing arr's space
}

void partPrime(int * arr, int pos, int val)
{
  if(val <= 0)
    {
      printArr(arr, pos);
      return;
    }
  int i;
  for(i=1; i<=val ; ++i)
    {
      // creates a partition of i is prime using isPrime function
      if(isPrime(i))
	{
	  arr[pos]=i;
	  partPrime(arr, pos+1, val-i);
	}
    }
}

// function for checking if the number is prime
int isPrime(int val)
{
  // if the number is 1 or divisible by 2, its not prime
  if(val==1 || (val > 2 && val%2==0))
    return 0;

  int max = val/2;
  int i;
  // checks numbers over 3 by dividing it by odd numbers
  for(i=3; i< max; i+=2)
    if(val%i==0)
      return 0;

  // if it is not divisible by anything but itself, return 1 = true
  return 1;
}
