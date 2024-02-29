#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct node
{
  double item;
  struct node *next;
};

static inline void cleanup_stack(struct node *head);
static inline int evaluate_one(struct node **head, char op);

int main(void)
{
  struct node *head = NULL;
  struct node *newNode = NULL;
  double temp;
  int ch, temp_ch;

  while (1)
  {
    ch = getchar();
    switch (ch)
    {
    case '\n':
    case EOF:
      goto end_of_input_loop;
    case '(':
    case ')':
    case ' ':
      continue;
    case '+':
    case '-':
      temp_ch = getchar();
      ungetc(temp_ch, stdin);
      if (isdigit(temp_ch))
      {
        ungetc(ch, stdin);
        goto handle_digit;
      }
    case '*':
    case '/':
      evaluate_one(&head, ch);
      break;
    default:
      if (isdigit(ch))
      {
handle_digit:
        ungetc(ch, stdin);
        
        newNode = malloc(sizeof (struct node));
        if (newNode == NULL)
        {
          cleanup_stack(head);
          return 1;
        }

        if (scanf("%lf", &newNode->item) != 1)
        {
          free(newNode);
          cleanup_stack(head);
          return 2;
        }

        newNode->next = head;
        head = newNode;
      }
      else
      {
        cleanup_stack(head);
        return 2;
      }
      break;
    }
  }
end_of_input_loop:

  if (head == NULL)
    return 3;
  
  if (head->next != NULL)
  {
    cleanup_stack(head);
    return 2;
  }

  printf("Result of Evaluation: %g\n", head->item);

  cleanup_stack(head);
  return 0;
}

static inline void cleanup_stack(struct node *head)
{
  struct node *temp;

  while ((temp = head))
  {
    head = temp->next;
    free(temp);
  }
}

static inline int evaluate_one(struct node **head, char op)
{
  double lhs, rhs;
  struct node *temp;

  if ((*head) == NULL || (*head)->next == NULL)
    return 2;

  rhs = (*head)->item;
  temp = (*head);
  (*head) = temp->next;
  free(temp);

  lhs = (*head)->item;
  temp = (*head);
  (*head) = temp->next;
  free(temp);

  temp = malloc(sizeof (struct node));
  if (temp == NULL)
    return 1;
  temp->next = (*head);
  switch (op)
  {
  case '+':
    temp->item = lhs + rhs;
    break;
  case '-':
    temp->item = lhs - rhs;
    break;
  case '*':
    temp->item = lhs * rhs;
    break;
  case '/':
    temp->item = lhs / rhs;
    break;
  default:
    free(temp);
    return 3;
  }

  (*head) = temp;

  return 0;
}
