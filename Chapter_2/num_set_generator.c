/**
 * @file    num_set_generator.c
 * @brief   generate a sequence of positive int
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int file_exist(const char *filename);
int get_first_char(void);
void consume_line(void);
unsigned long * num_set_generator(unsigned long size, unsigned long upper_bound);

int main(int argc, char **argv)
{
  FILE *file;
  unsigned long data_size, upper_range;
  unsigned long *arr, *arr_ed;
  char *cptr;

  if (argc != 3)
  {
    fprintf(stderr, "Usage: %s output_file data_size\n", argv[0]);
    return 1;
  }
  if (file_exist(argv[1]))
  {
    int choice;
    printf("%s already exist, Do you want to replace that file? [y to confirm]\n",
           argv[1]);
    choice = get_first_char();
    consume_line();
    if (tolower(choice) != 'y')
    {
      puts("Non-y detected, leaving the program.");
      return 2;
    }
  }
  file = fopen(argv[1], "w");
  if (file == NULL)
  {
    fprintf(stderr, "Failed to open %s for writing.\n", argv[1]);
    return 2;
  }
  data_size = strtoul(argv[2], &cptr, 10);
  if (*cptr != '\0')
  {
    fprintf(stderr, "\"%s\" is not plain number.\n", argv[2]);
    fclose(file);
    return 3;
  }

  arr = num_set_generator(data_size, data_size / 2);
  if (arr == NULL)
  {
    fputs("Failed to generate data set\n", stderr);
    fclose(file);
    return -1;
  }
  arr_ed = arr + data_size;

  fprintf(file, "%lu\n", data_size);
  for (unsigned long *iter = arr; iter != arr_ed; iter++)
    fprintf(file, "%lu\n", *iter);

  free(arr);
  fclose(file);

  return 0;
}

int file_exist(const char *filename)
{
  FILE *fp = fopen(filename, "r");
  if (fp)
  {
    fclose(fp);
    return 1;
  }
  else
    return 0;
}

int get_first_char(void)
{
  int ch;
  
  while ((ch = getchar()) != EOF && isspace(ch))
    continue;

  return ch;
}

void consume_line(void)
{
  int ch;

  while ((ch = getchar()) != EOF && ch != '\n')
    continue;
}

unsigned long * num_set_generator(unsigned long size, unsigned long upper_bound)
{
  int pow_ct = 0, val = RAND_MAX;
  unsigned long *ret = malloc(size * sizeof (unsigned long));
  unsigned long *iter, *ret_ed;

  if (ret == NULL)
    return NULL;
  ret_ed = ret + size;
  iter = ret;

  while (val)
  {
    val /= 2;
    pow_ct++;
  }
  srand((unsigned) time(NULL));
  
  if (upper_bound > RAND_MAX)
    while (iter != ret_ed)
      *iter++ = (((unsigned long)rand() << pow_ct) | (unsigned long)rand()) % upper_bound;
  else
    while (iter != ret_ed)
      *iter++ = (unsigned long) rand() % upper_bound;

  return ret;
}
