#include <stdio.h>
#include <stdlib.h>

#include "transaction.h"
#include "../elem_sorts.h"


typedef struct transaction_arr
{ Transaction *st, *cav, *ed; }
Transaction_arr;

int transaction_cmp_amount_wrapper(const void *lhs, const void *rhs)
{ return transaction_cmp_amount((Transaction*)lhs, (Transaction*)rhs); }

void init_transaction_arr(Transaction_arr *this);
int transaction_arr_add(Transaction_arr *this, Transaction *new_transaction);
void transaction_arr_cleanup(Transaction_arr *this);
void transaction_arr_print(Transaction_arr *this);


int main(int argc, char **argv)
{
  FILE *infile;
  char c;
  Transaction temp;
  Transaction_arr transaction_list;

  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s input_data_file\n", argv[0]);
    return 2;
  }

  infile = fopen(argv[1], "r");
  if (infile == NULL)
  {
    fprintf(stderr, "Failed to open %s for reading\n", argv[1]);
    return 2;
  }

  init_transaction_arr(&transaction_list);
  for (size_t i = 0; !feof(infile); i++)
  {
    if (fscanf(infile, "%d,%u,%d,%u",
               &temp.date.month, &temp.date.day, 
               &temp.date.year, &temp.amount) != 4)
    {
      switch(getc(infile))
      {
        case '\n':
          continue;
        case EOF:
          goto finish_reading_infile;
        default:
          break;
      }
      fprintf(stderr, "Failed to parse line %zu\n", i + 1);
    }
    else
      if (transaction_arr_add(&transaction_list, &temp))
      {
        fputs("Failed to add item to transaction list, terminating the program...\n", stderr);
        transaction_arr_cleanup(&transaction_list);
        return 1;
      }

    // consume rest of the line
    fscanf(infile, "%*[^\n]\n");
  }
finish_reading_infile:

  fputs("Loaded Transactions: ", stdout);
  transaction_arr_print(&transaction_list);
  putchar('\n');

  shell_sort(transaction_list.st, transaction_list.cav, 
             sizeof(Transaction), &transaction_cmp_amount_wrapper);

  fputs("Sorted Transactions: ", stdout);
  transaction_arr_print(&transaction_list);
  putchar('\n');

  transaction_arr_cleanup(&transaction_list);

  return 0;
}


void init_transaction_arr(Transaction_arr *this)
{ this->st = this->cav = this->ed = NULL; }

int _transaction_arr_expand(Transaction_arr *this)
{
  Transaction *temp;
  size_t new_capacity = this->ed - this->st;

  if (new_capacity)
    new_capacity *= 2;
  else
    new_capacity = 1;

  temp = realloc(this->st, new_capacity * sizeof(Transaction));
  if (temp == NULL)
    return 1;

  this->cav = temp + (this->cav - this->st);
  this->st = temp;
  this->ed = temp + new_capacity;

  return 0;
}

int transaction_arr_add(Transaction_arr *this, Transaction *new_transaction)
{
  if (this->cav == this->ed && _transaction_arr_expand(this))
    return 1;

  *this->cav++ = *new_transaction;

  return 0;
}

void transaction_arr_cleanup(Transaction_arr *this)
{ free(this->st); }

void transaction_arr_print(Transaction_arr *this)
{
  putchar('{');

  for (Transaction *iter = this->st; iter < this->cav; iter++)
  {
    transaction_print(iter);
    fputs(", ", stdout);
  }

  putchar('}');
  putchar('\n');
}
