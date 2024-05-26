#include <stdio.h>
#include <stdlib.h>

#include "date.h"
#include "crate_list.h"
#include "../elem_sorts.h"


int Date_cmp_wrapper(const void *lhs, const void *rhs);


int main(int argc, char **argv)
{
  FILE *infile;
  Date temp;
  struct crate_list crate_list;

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

  init_crate_list(&crate_list);
  // extract data from infile
  for (size_t i = 0; !feof(infile); i++)
  {
    if (fscanf(infile, "%d,%u,%d", &temp.month, &temp.day, &temp.year) == 3)
    {
      if (crate_list_add(&crate_list, temp))
      {
        fputs("Failed to add a new crate to the crate list, program stopped!\n", stderr);
        free(crate_list.shipping_dates);
        fclose(infile);
        return 1;
      }
    }
    else
    {
      fprintf(stderr, "Failed to parse line %zu\n", i);
      continue;
    }

    fscanf(infile, "%*[^\n]\n");
  }
  fclose(infile);

  printf("%td crate", crate_list.shipping_dates_cav - crate_list.shipping_dates);
  if ((crate_list.shipping_dates_cav - crate_list.shipping_dates) == 1)
    puts(" is loaded: ");
  else
    puts("s are loaded: ");

  crate_list_print(&crate_list);

  selection_sort(crate_list.shipping_dates, crate_list.shipping_dates_cav, 
                 sizeof(Date), &Date_cmp_wrapper);

  fputs("Rearranged Crates: ", stdout);
  crate_list_print(&crate_list);

  free(crate_list.shipping_dates);
  return 0;
}


int Date_cmp_wrapper(const void *lhs, const void *rhs)
{ return Date_cmp(*(Date*)lhs, *(Date*)rhs); }
