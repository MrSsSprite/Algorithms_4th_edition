#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

struct _card_queue_node
{
  struct card card;
  struct _card_queue_node *next;
};

struct card_queue
{
  struct _card_queue_node *first, *sorted, *last;
  size_t size;
};


struct card_queue * init_cardQueue(void)
{
  struct card_queue *ret = malloc(sizeof(struct card_queue));

  if (ret == NULL)
    return NULL;

  ret->first = ret->last = ret->sorted = NULL;
  ret->size = 0;

  return ret;
}

struct card_queue * init_cardQueue_arr(struct card *first, struct card *last)
{
  struct card_queue *ret;
  struct _card_queue_node *temp_node;
  struct card *iter;

  if (first == last)
    return init_cardQueue();

  ret = malloc(sizeof(struct card_queue));
  if (ret == NULL)
    return NULL;

  // first node
  iter = first;
  temp_node = malloc(sizeof(struct _card_queue_node));
  if (temp_node == NULL)
  {
    free(ret);
    return NULL;
  }
  temp_node->card = *iter++;
  ret->first = temp_node;

  // other node(s)
  while (iter < last)
  {
    temp_node->next = malloc(sizeof(struct _card_queue_node));
    if (temp_node->next == NULL)
    {
      for (temp_node = ret->first; temp_node; temp_node = ret->first)
      {
        ret->first = temp_node->next;
        free(temp_node);
      }

      free(ret);
      return NULL;
    }
    temp_node->next->card = *iter++;
    temp_node = temp_node->next;
  }

  ret->sorted = temp_node->next = NULL;
  ret->last = temp_node;
  ret->size = last - first;

  return ret;
}

void cardQueue_cleanup(struct card_queue *this)
{
  for (struct _card_queue_node *temp_node = this->first;
       temp_node; temp_node = this->first)
  {
    this->first = temp_node->next;
    free(temp_node);
  }

  free(this);
}

int cardQueue_cmp_top2(struct card_queue *this)
{ return card_cmp(&this->first->card, &this->first->next->card); }

void cardQueue_exch_top2(struct card_queue *this)
{
  struct _card_queue_node *temp_node;

  temp_node = this->first->next;
  this->first->next = temp_node->next;
  temp_node->next = this->first;
  this->first = temp_node;
}

struct _card_queue_node * cardQueue_move_top_to_bottom(struct card_queue *this)
{
  struct _card_queue_node *temp = this->first,
                          *ret = this->sorted;

  this->first = temp->next;
  if (ret)
  {
    temp->next = ret->next;
    ret->next = temp;
    this->sorted = temp;
    return ret;
  }
  else
  {
    ret = this->last;
    temp->next = ret->next;
    ret->next = temp;
    this->last = temp;
    return ret;
  }
}

void cardQueue_set_sorted(struct card_queue *this, struct _card_queue_node *node)
{ this->sorted = node; }

int cardQueue_all_sorted(struct card_queue *this)
{ return this->sorted == this->first; }

void print_deck(struct card_queue *this)
{
  char *suit, *rank;
  
  putchar('{');

  for (struct _card_queue_node *iter = this->first; iter; iter = iter->next)
  {
    switch (iter->card.suit)
    {
      case joker:
        fputs("Joker, ", stdout);
        continue;
      case diamond:
        suit = "Diamond";
        break;
      case club:
        suit = "Club";
        break;
      case heart:
        suit = "Heart";
        break;
      case spade:
        suit = "Spade";
        break;
      default:
        suit = "Unknown";
    }

    switch (iter->card.rank)
    {
    case 11:
      rank = "J";
      break;
    case 12:
      rank = "Q";
      break;
    case 13:
      rank = "K";
      break;
    default:
      printf("%s-%hu, ", suit, iter->card.rank);
      continue;
    }

    printf("%s-%c, ", suit, *rank);
  }

  putchar('}');
  putchar('\n');
}
