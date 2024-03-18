#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "knuth_shuffle.h"
#include "quicksort.h"

void print_arr(unsigned long *arr, unsigned long arr_sz);

int cmp_lu(const void *lhs, const void *rhs);

int main(int argc, char **argv)
{
  unsigned long arr_sz;
  unsigned long *arr;
  char *endptr;

  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s sizeof_arr\n", argv[0]);
    return 2;
  }

  arr_sz = strtoul(argv[1], &endptr, 10);
  if (endptr == argv[1])
  {
    fputs("sizeof_arr must be a positive integer\n", stderr);
    return 2;
  }

  arr = malloc(arr_sz * sizeof (unsigned long));
  if (arr == NULL)
  {
    fputs("Failed to malloc for array\n", stderr);
    return 1;
  }

  for (unsigned long i = 0; i < arr_sz; i++)
    arr[i] = i;
  puts("The original arr:");
  print_arr(arr, arr_sz);

  knuth_shuffle(arr, arr + arr_sz, sizeof (unsigned long));
  puts("The shuffled arr:");
  print_arr(arr, arr_sz);

  quick_sort(arr, arr + arr_sz, sizeof (unsigned long), &cmp_lu);
  puts("The sorted arr:");
  print_arr(arr, arr_sz);

  free(arr);
  return 0;
}

void print_arr(unsigned long *arr, unsigned long arr_sz)
{
  for (unsigned long *iter = arr, *arr_ed = arr + arr_sz;
       iter < arr_ed; iter++)
    printf("%lu, ", *iter);

  putchar('\n');
}

int cmp_lu(const void *lhs, const void *rhs)
{ return *(unsigned long *)lhs - *(unsigned long *)rhs; }
