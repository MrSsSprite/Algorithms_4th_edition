/**
 * @file    driver function for sort
 */
#include <stdio.h>
#include <stdlib.h>
#include "elem_sorts.h"
#include "mergesort.h"

int ul_cmp(const void *lhs, const void *rhs)
{ return *(const unsigned long*)lhs - *(const unsigned long*)rhs; }

void consume_line(FILE *fp);

#define sorter_function \
/* Modify the name below to determine
   the sorter function */\
  BU_merge_sort

int main(int argc, char **argv)
{
  FILE *file;
  size_t data_size;
  unsigned long *arr, *arr_ed;
  unsigned long *iter, val;
  int counter, max_dig, item_per_line;

  if (argc != 2 && argc != 3)
  {
    fprintf(stderr, "Usage: %s infile [outfile]\n", argv[0]);
    return 1;
  }

  if ((file = fopen(argv[1], "r")) == NULL)
  {
    fprintf(stderr, "Failed to open %s for reading.\n", argv[1]);
    return 2;
  }

  if (fscanf(file, "%zd", &data_size) != 1)
  {
    fputs("Invalid File Format.\n", stderr);
    fclose(file);
    return 3;
  }
  consume_line(file);
  arr = malloc(data_size * sizeof (unsigned long));
  if (arr == NULL)
  {
    fputs("Failed to malloc\n", stderr);
    fclose(file);
    return -1;
  }
  arr_ed = arr + data_size;

  iter = arr;
  while (iter != arr_ed && !feof(file))
  {
    if (fscanf(file, "%lu", &val) != 1)
    {
      fputs("Invalid Value Detected. Rest of the line skipped.\n", stderr);
      consume_line(file);
      continue;
    }

    *iter++ = val;
  }

  fclose(file);

  if (iter != arr_ed)
  {
    fputs("Values provided not enough. Filling other slots with 0s.\n", stderr);
    while (iter != arr_ed)
      *iter++ = 0;
  }

  sorter_function(arr, arr_ed, sizeof(unsigned long), ul_cmp);

  // calculation for formatting
  val = *(arr_ed - 1);
  max_dig = 0;
  while (val)
  {
    val /= 10;
    max_dig++;
  }
  if (max_dig == 0)
    max_dig = 1;
  item_per_line = 100 / (max_dig + 2);
  if (item_per_line ==  0)
    item_per_line = 1;

  if (argc == 2)
  {
    puts("The sorted arr:");
    iter = arr;
    counter = 0;
    while (iter != arr_ed)
    {
      printf("%*lu, ", max_dig, *iter++);
      if (++counter == item_per_line)
      {
        putchar('\n');
        counter = 0;
      }
    }
    putchar('\n');
  }
  else
  {
    file = fopen(argv[2], "w");
    if (file == NULL)
    {
      fprintf(stderr, "Failed to open %s for writing.\n", argv[2]);
      free(arr);
      return 4;
    }
    fprintf(file, "%zd\n", data_size);
    iter = arr;
    while (iter != arr_ed)
      fprintf(file, "%lu\n", *iter++);
    fclose(file);
  }

  free(arr);

  return 0;
}

void consume_line(FILE *fp)
{
  int ch;

  while ((ch = getc(fp)) != EOF && ch != '\n')
    continue;
}
