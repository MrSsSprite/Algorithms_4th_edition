#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <stddef.h>

typedef struct union_find* UF;

/**
 * @breif   create a new UF object
 * @param   data_size   total amount of sites
 * @return  the dynamically allocated UF obj
 */
UF init_UF(size_t data_size);
/**
 * @brief   get the total amount of components
 * @param   this    the UF obj
 * @return  amount of components
 */
size_t UF_count(UF this);
/**
 * @brief   the root index of the site
 * @param   this    the UF obj
 * @param   p       site numer
 * @return  root index of the given site
 */
size_t UF_find(UF this, size_t p);
/**
 * @brief   check if two sites are connected
 * @param   this    the UF obj
 * @param   p       site 0
 * @param   q       site 1
 * @return  0 for NOT connected; non-0 otherwise.
 */
int UF_connected(UF this, size_t p, size_t q)
{ return UF_find(p) == UF_find(q); }
/**
 * @brief   try to union two sites
 * @param   this    the UF obj
 * @param   p       site 0
 * @param   q       site 1
 * @return  0: connected before function call; 1: action taken
 */
int UF_union(UF this, size_t p, size_t q);

// memory clean up; similar to fclose
void clean_UF(UF this);

#endif
