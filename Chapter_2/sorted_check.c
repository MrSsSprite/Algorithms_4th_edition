/**
 * @file    sorted_check.c
 * @brief   check if the sequence of numbers output file produced by sort driver (or 
 *          similar format text file) is sorted
 */
#include <stdio.h>
#include <stdlib.h>

void consume_line(FILE *fp);

int main(int argc, char **argv)
{
  FILE *file;
  size_t data_size;
  unsigned long *arr, *arr_ed;
  unsigned long *iter, val;
  int error_found = 0;

  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s input_file\n", argv[0]);
    return 1;
  }
  
  file = fopen(argv[1], "r");
  if (file == NULL)
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
    fputs("Failed to malloc for arr\n", stderr);
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
    fprintf(stderr, "Only %zd numbers loaded (indicated size: %zd)\n",
            (size_t)(iter - arr), data_size);
    arr_ed = iter;
  }

  for (iter = arr + 1; iter < arr_ed; iter++)
  {
    if (*iter < *(iter - 1))
    {
      printf("%lu(#%td) is greater than %lu(#%td)\n",
             *(iter - 1), (iter - 1) - arr, *iter, iter - arr);
      error_found = 1;
      break;
    }
  }

  if (!error_found)
    puts("The array is sorted");

  free(arr);

  return 0;
}

void consume_line(FILE *fp)
{
  int ch;

  while ((ch = getc(fp)) != EOF && ch != '\n')
    continue;
}
