#ifndef QUEUE_H
#define QUEUE_H

#include "../card.h"

typedef struct card_queue* cardQueue;
typedef struct _card_queue_node* cardQueue_iter;


cardQueue init_cardQueue(void);
cardQueue init_cardQueue_arr(struct card *first, struct card *last);
void cardQueue_cleanup(cardQueue this);

int cardQueue_cmp_top2(cardQueue this);
void cardQueue_exch_top2(cardQueue this);
cardQueue_iter  cardQueue_move_top_to_bottom(cardQueue this);
void cardQueue_set_sorted(cardQueue this, cardQueue_iter node);
int cardQueue_all_sorted(cardQueue this);

void print_deck(cardQueue this);

#endif
