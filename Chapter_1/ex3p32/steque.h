#ifndef STEQUE_H
#define STEQUE_H

#include <stddef.h>

#define _STEQUE_DATA_TYPE  int

typedef struct _steque_node
{
  _STEQUE_DATA_TYPE item;
  struct _steque_node *next;
} * Steque_iter;
typedef struct steque* Steque;

/**
 * @brief   return a Steque object
 * @return  Steque object (need to be freed using clean_steque)
 * @see     clean_steque
 */
Steque init_steque(void);
/**
 * @brief   clean a Steque object that's initialized through init_steque
 */
void clean_steque(Steque this);

/**
 * @brief   push an item to a Steque
 * @param   this  the Steque object
 * @param   item  item to be pushed
 * @reutrn  0 for successful; failure otherwise
 */
int steque_push(Steque this, _STEQUE_DATA_TYPE item);
/**
 * @brief   enqueue an item to a Steque
 * @param   this  the Steque object
 * @param   item  item to be enqueued
 * @reutrn  0 for successful; failure otherwise
 */
int steque_enqueue(Steque this, _STEQUE_DATA_TYPE item);
/**
 * @brief   pop an item from the Steque
 * @param   Steque  the Steque object
 * @return  the item poped from the Steque; undefined if the Steque is empty
 */
_STEQUE_DATA_TYPE steque_pop(Steque this);

// return NULL for failure
Steque_iter steque_first(Steque this);
Steque_iter steque_last(Steque this);

// return value is undefined if Steque is empty
_STEQUE_DATA_TYPE steque_front(Steque this);
_STEQUE_DATA_TYPE steque_back(Steque this);

size_t steque_size(Steque this);

#endif
