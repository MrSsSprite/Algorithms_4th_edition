#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node
{
  int value;
  struct node *next;
};

static inline void cleanup_node(struct node *head);
struct node * reverse(struct node *head);

int main(int argc, char **argv)
{
  struct node *head = NULL, **iter;
  long max;
  char *endptr;

  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s data_size\n", argv[0]);
    return 2;
  }

  max = strtol(argv[1], &endptr, 10);

  if (endptr == argv[1])
  {
    fprintf(stderr, "no valid numeric value found at the beginning of %s\n", argv[1]);
    return 2;
  }
  if (max < 1)
  {
    fputs("data_size must be greater than 0\n", stderr);
    return 2;
  }
  if (max > INT_MAX)
  {
    fprintf(stderr, "The data_size (%ld) must not be greater than %d.\n", max, INT_MAX);
    return 2;
  }

  head = malloc(sizeof (struct node));
  if (head == NULL)
  {
    fputs("Failed to allocate memory for head.", stderr);
    return 1;
  }
  head->value = 0;
  head->next = NULL;
  iter = &head->next;
  for (int i = 1; i < max; i++)
  {
    *iter = malloc(sizeof (struct node));
    if (*iter == NULL)
    {
      fprintf(stderr, "Failed to malloc for %dth node.\n", i);
      cleanup_node(head);
      return 1;
    }

    (*iter)->value = i;
    (*iter)->next = NULL;
    iter = &(*iter)->next;
  }

  puts("Generated values:");
  for (iter = &head; *iter; iter = &(*iter)->next)
    printf("%d\n", (*iter)->value);

  head = reverse(head);
  puts("Reversed values:");
  for (iter = &head; *iter; iter = &(*iter)->next)
    printf("%d\n", (*iter)->value);

  cleanup_node(head);

  return 0;
}

static inline void cleanup_node(struct node *head)
{
  struct node *temp;

  while (head)
  {
    temp = head;
    head = head->next;
    free(temp);
  }
}

struct node * reverse(struct node *head)
{
  struct node *newHead = NULL, *temp;

  while (head)
  {
    temp = head;
    head = head->next;
    temp->next = newHead;
    newHead = temp;
  }

  return newHead;
}
