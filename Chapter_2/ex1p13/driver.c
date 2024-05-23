#include <stdio.h>
#include <stdlib.h>

#include "card.h"
#include "../elem_sorts.h"
#include "../knuth_shuffle.h"


void print_deck(struct card *deck);


const unsigned int DECK_SIZE = 13 * 4;


int main(int argc, char **argv)
{
  FILE *infile;
  struct card *deck, *deck_ed;
  struct card *iter;

  if (argc > 2)
  {
    fprintf(stderr, "Usage: %s [input_data_file]\n", argv[0]);
    return 2;
  }

  deck = malloc(DECK_SIZE * sizeof(struct card));
  if (deck == NULL)
  {
    fputs("Failed to allocate memory for a deck\n", stderr);
    return 1;
  }
  deck_ed = deck + DECK_SIZE;

  iter = deck;
  if (argc < 2)
  {
    for (enum suit suit = diamond; suit <= spade; suit++)
      for (unsigned short rank = 1; rank <= 13; rank++)
      {
        iter->suit = suit;
        iter->rank = rank;
        iter++;
      }
  }
  else
  {
    infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
      fprintf(stderr, "Failed to open %s for reading\n", argv[1]);
      free(deck);
      return 2;
    }

    for (int i = 0; iter < deck_ed && !feof(infile); i++)
    {
      if (fscanf(infile, "%d,%hu", &iter->suit, &iter->rank) == 2)
        iter++;
      else
        fprintf(stderr, "Failed to parse line %d\n", i + 1);

      // consume the rest of this line
      fscanf(infile, "%*[^\n]\n");
    }

    if (iter != deck + DECK_SIZE)
    {
      if (iter == deck + 1)
        fputs("Since the card provided is not enough to fill the deck, \"Joker\" cards "
              "are filled in as placeholders\n", stderr);
      else if (iter == deck + DECK_SIZE - 1)
        fputs("Since the cards provided are not enough to fill the deck, \"Joker\" card "
              "is filled in as placeholders\n", stderr);
      else
        fputs("Since the cards provided are not enough to fill the deck, \"Joker\" cards "
              "are filled in as placeholders\n", stderr);

      while (iter < deck_ed)
      {
        iter->suit = joker;
        iter->rank = 0;
        iter++;
      }
    }
  }

  fputs("Initial Deck: ", stdout);
  print_deck(deck);

  if (argc < 2)
  {
    knuth_shuffle(deck, deck + DECK_SIZE, sizeof(struct card));
    fputs("Shuffled Deck: ", stdout);
    print_deck(deck);
  }

  shell_sort(deck, deck_ed, sizeof(struct card), &card_cmp_wrapper);

  fputs("Sorted Deck: ", stdout);
  print_deck(deck);

  free(deck);
  return 0;
}

void print_deck(struct card *deck)
{
  char *suit, *rank;
  putchar('{');
  for (int i = 0; i < DECK_SIZE; i++)
  {
    switch (deck[i].suit)
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

    switch (deck[i].rank)
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
      printf("%s-%hu, ", suit, deck[i].rank);
      continue;
    }

    printf("%s-%c, ", suit, *rank);
  }

  putchar('}');
  putchar('\n');
}
