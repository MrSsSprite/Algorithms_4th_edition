#include <stdio.h>

#include "union_find.h"

void consume_line(void);

int main(int argc, char **argv)
{
  size_t data_size;
  size_t p, q;
  UF uf;

  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s data_size\n", argv[0]);
    return 1;
  }
  if (sscanf(argv[1], "%zd", &data_size) != 1)
  {
    fputs("The first argument must be an integer.\n", stdout);
    return 2;
  }

  if ((uf = init_UF(data_size)) == NULL)
  {
    fputs("Failed to initialize uf.\n", stderr);
    return -1;
  }

  printf("Input %zd set of numbers, 2 numbers per line, separated by whitespace.\n", data_size);
  for (size_t i = 0; i < data_size; i++)
  {
    if (scanf("%zd %zd", &p, &q) != 2)
    {
      fprintf(stderr, "Failed to scan line %zd.\n", i);
      continue;
    }
    else if (q >= data_size || p >= data_size)
      fputs("Invalid Input.\n", stdout);
    else if (UF_union(uf, p, q))
      printf("Connection built between %zd and %zd.\n", p, q);

    consume_line();
  }

  fputs("Input 2 numbers to see if they are connected, input q to quit.\n", stdout);
  while (scanf("%zd %zd", &p, &q) == 2)
  {
    if (q >= data_size || p >= data_size)
    {
      fputs("Invalid Input.\n", stdout);
      continue;
    }
    printf("%zd and %zd are ", p, q);
    if (!UF_connected(uf, p, q))
      fputs("not ", stdout);
    fputs("connected.\n", stdout);
    
    consume_line();
  }

  fputs("Cleaning memory...\n", stdout);
  clean_UF(uf);
  fputs("Finished.\n", stdout);

  return 0;
}

void consume_line(void)
{
  int ch;

  while ((ch = getchar()) != EOF && ch != '\n')
    continue;
}
