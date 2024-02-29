#include "doublyll.h"

#include <stdlib.h>

struct dbll
{
  struct dbll_node *first, *last;
  size_t count;
};

struct dbll * init_dbll(void)
{
  struct dbll *ret = malloc(sizeof (struct dbll));

  if (ret == NULL)
    return NULL;

  ret->first = ret->last = NULL;
  ret->count = 0;

  return ret;
}

void cleanup_dbll(struct dbll *this)
{
  struct dbll_node *temp;

  while (this->first)
  {
    temp = this->first;
    this->first = temp->next;
    free(temp);
  }

  free(this);
}

int dbll_push_front(struct dbll *this, DBLL_ITEM_TYPE item)
{
  struct dbll_node *newNode = malloc(sizeof (struct dbll_node));

  if (newNode == NULL)
    return 1;
  newNode->item = item;
  newNode->prev = NULL;
  newNode->next = this->first;

  if (this->last == NULL)
    this->last = newNode;
  else
    this->first->prev = newNode;
  this->first = newNode;

  this->count++;
  return 0;
}

int dbll_push_back(struct dbll *this, DBLL_ITEM_TYPE item)
{
  struct dbll_node *newNode = malloc(sizeof (struct dbll_node));

  if (newNode == NULL)
    return 1;
  newNode->item = item;
  newNode->next = NULL;
  newNode->prev = this->last;

  if (this->first == NULL)
    this->first = newNode;
  else
    this->last->next = newNode;
  this->last = newNode;

  this->count++;
  return 0;
}

DBLL_ITEM_TYPE dbll_pop_front(struct dbll *this)
{
  DBLL_ITEM_TYPE ret;
  struct dbll_node *temp;

  if ((temp = this->first))
  {
    ret = temp->item;
    if ((this->first = temp->next) == NULL)
      this->last = NULL;
    else
      this->first->prev = NULL;
    free(temp);
  }
  else
    return ret;

  this->count--;
  return ret;
}

DBLL_ITEM_TYPE dbll_pop_back(struct dbll *this)
{
  DBLL_ITEM_TYPE ret;
  struct dbll_node *temp;

  if ((temp = this->last))
  {
    ret = temp->item;
    if ((this->last = temp->prev) == NULL)
      this->first = NULL;
    else
      this->last->next = NULL;
    free(temp);
  }
  else
    return ret;

  this->count--;
  return ret;
}

struct dbll_node * dbll_insert_before(struct dbll *this, struct dbll_node *pos, DBLL_ITEM_TYPE item)
{
  struct dbll_node *nptr;
  struct dbll_node *newNode;

  if (pos == NULL)
    return NULL;

  nptr = pos->prev;

  newNode = malloc(sizeof (struct dbll_node));
  if (newNode == NULL)
    return NULL;
  newNode->item = item;
  newNode->prev = nptr;
  newNode->next = pos;

  if (nptr)
    nptr->next = newNode;
  pos->prev = newNode;

  if (pos == this->first)
    this->first = newNode;
  this->count++;
  return newNode;
}

struct dbll_node * dbll_insert_after(struct dbll *this, struct dbll_node *pos, DBLL_ITEM_TYPE item)
{
  struct dbll_node *nptr;
  struct dbll_node *newNode;

  if (pos == NULL)
    return NULL;

  nptr = pos->next;

  newNode = malloc(sizeof (struct dbll_node));
  if (newNode == NULL)
    return NULL;
  newNode->item = item;
  newNode->prev = pos;
  newNode->next = nptr;

  if (nptr)
    nptr->prev = newNode;
  pos->next = newNode;

  if (pos == this->last)
    this->last = newNode;
  this->count++;
  return newNode;
}

struct dbll_node * dbll_erase(struct dbll *this, struct dbll_node *pos)
{
  struct dbll_node *nptr;

  if (pos == NULL)
    return NULL;

  if (pos == this->first)
  {
    if ((nptr = pos->next) == NULL)
      this->last = NULL;
    else
      nptr->prev = NULL;

    this->first = nptr;
  }
  else if (pos == this->last)
  {
    if ((nptr = pos->prev) == NULL)
      this->first = NULL;
    else
      nptr->next = NULL;

    this->last = nptr;
  }
  else
  {
    nptr = pos->next;
    pos->prev->next = nptr;
    pos->next->prev = pos->prev;
  }

  free(pos);
  this->count--;
  return nptr;
}

struct dbll_node * dbll_begin(struct dbll *this)
{ return this->first; }

struct dbll_node * dbll_end(struct dbll *this)
{ return this->last; }

DBLL_ITEM_TYPE dbll_front(struct dbll *this)
{ return this->first->item; }

DBLL_ITEM_TYPE dbll_back(struct dbll *this)
{ return this->last->item; }

size_t dbll_count(struct dbll *this)
{ return this->count; }
