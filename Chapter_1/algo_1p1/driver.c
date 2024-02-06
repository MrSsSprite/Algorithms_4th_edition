#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"

char * get_word(void);

int main(void)
{
  struct Stack stack;
  char *string;
  char **sptr;
  init_Stack(&stack, sizeof(char*));

  puts("Enter a word to push to the Stack, '-' to pop from the Stack");
  fputs("Input the command (# on a newline to leave):\n", stdout);
  while ((string = get_word()) && string[0] != '#')
  {
    if (strcmp(string, "-") == 0)
    {
      free(string);
      sptr = pop(&stack);
      if (sptr)
      {
        puts(*sptr);
        free(*sptr);
        free(sptr);
      }
      else
        fprintf(stderr, "Failed to pop\n");

      continue;
    }

    if (push(&stack, &string))
    {
      fputs("Error when pushing, leaving the loop\n", stderr);
      free(string);
      break;
    }
  }

  if (string)
    free(string);

  puts("Freeing the memory");
  while ((sptr = pop(&stack)))
  {
    free(*sptr);
    free(sptr);
  }
  puts("Done!");

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
