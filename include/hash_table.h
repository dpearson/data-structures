/*
 *  hash_table.h
 *  Data Structures
 *
 *  Created by David Pearson on 7/29/13.
 *  Copyright (c) 2013 David Pearson. All rights reserved.
 */

#ifndef Data_Structures_hash_table_h
#define Data_Structures_hash_table_h

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dll.h"

typedef struct {
	/* The hash function used to build the table
	 */
	unsigned int (*hash_function)(char *);
	
	/* The number of buckets allocated for the table
	 */
	unsigned int bucket_count;
	
	/* The number of occupied buckets
	 */
	unsigned int occupied_buckets;
	
	/* The number of items in the table
	 */
	unsigned int length;
	
	/* An array of pointers to the linked lists
	 * actually used to store items
	 */
	ll_dlist **items;
} hash_table;

extern hash_table *hash_table_new();
extern bool hash_table_set(hash_table *table, void *elem, char *key, void (*release_function)(void *));
extern void *hash_table_get(hash_table *table, char *key);
extern void hash_table_free(hash_table *table);

#endif
