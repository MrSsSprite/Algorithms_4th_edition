#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../algo_1p2/_stack_node.h"
#include "bag.h"

char * get_word(void);

int main(void)
{
  char *string;
  Bag_iter iter;
  Bag bag;
  init_Bag(&bag, sizeof (char*));

  puts("Enter words to pack into the Bag ('#' to leave):");
  while ((string = get_word()) && string[0] != '#')
    if (add(&bag, &string))
    {
      fputs("Error when pushing, leaving the loop\n", stderr);
      free(string);
      break;
    }

  if (string)
    free(string);

  iter = get_bag_iter(&bag);

  for (int i = 0; iter; i++, iter = iter->next)
  {
    printf("Element #%d: %s\n", i, *(char**)iter->item);
    free(*(char**)iter->item);
  }

  puts("Clearing the bag.");
  clear(&bag);
  puts("Done.");

  return 0;
}

char * get_word(void)
{
  size_t cap = 1;
  char *string = malloc(cap), *cavity = string, *terminal = string + cap;
  char *temp;
  int ch;

  if (string == NULL)
    return NULL;

  // skip the preceding spaces
  while (ch = getchar(), isspace(ch))
    continue;
  if (ch != EOF)
    *cavity++ = ch;

  while ((ch = getchar()) != EOF && !isspace(ch))
  {
    if (cavity == terminal)
    {
      temp = realloc(string, cap * 2);
      if (temp == NULL)
      {
        free(string);
        return NULL;
      }
      string = temp;
      cavity = string + cap;
      terminal = string + (cap *= 2);
    }

    *cavity++ = ch;
  }

  if (cavity == terminal)
  {
    temp = realloc(string, cap + 1);
    if (temp == NULL)
    {
      free(string);
      return NULL;
    }
    string = temp;
    cavity = string + cap;
  }

  *cavity = '\0';

  return string;
}
