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
	unsigned int (*hash_function)(char *);
	unsigned int bucket_count;
	unsigned int occupied_buckets;
	unsigned int length;

	ll_dlist **items;
} hash_table;

extern hash_table *hash_table_new();
extern bool hash_table_set(hash_table *table, void *elem, char *key, void (*release_function)(void *));
extern void *hash_table_get(hash_table *table, char *key);
extern void hash_table_free(hash_table *table);

#endif
