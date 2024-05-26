#ifndef CARD_H
#define CARD_H

enum suit { joker = -1, diamond = 0, club, heart, spade };

struct card
{
  enum suit suit;
  unsigned short rank;
};

extern const unsigned int DECK_SIZE;


int card_cmp(const struct card *lhs, const struct card *rhs);
int card_cmp_wrapper(const void *lhs, const void *rhs);

#endif
