#include "../card.h"
#include "../../elem_sorts.h"


// operations
static inline int cmp_top2_cards(struct card *deck);
static inline void exch_top2_cards(struct card *deck);
static inline void move_top_to_bottom(struct card *deck, struct card *sorted);
