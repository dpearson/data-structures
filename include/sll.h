//
//  sll.h
//  Data Structures
//
//  Created by David Pearson on 6/1/12.
//  Copyright (c) 2012-2014 David Pearson. All rights reserved.
//

#ifndef Data_Structures_sll_h
#define Data_Structures_sll_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ll_selement {
	void *data;
	struct ll_selement *next;
	void (*release_function)(void *);
} ll_selement;

typedef struct {
	unsigned int length;
	ll_selement *first;
} ll_slist;

extern ll_slist *sll_new();
extern bool sll_insert(ll_slist *list, void *elem, int index, void (*release_function)(void *));
extern bool sll_prepend(ll_slist *list, void *elem, void (*release_function)(void *));
extern bool sll_append(ll_slist *list, void *elem, void (*release_function)(void *));
extern void *sll_get(ll_slist *list, int index);
extern void *sll_remove(ll_slist *list, int index);
extern void sll_clear(ll_slist *list);
extern void sll_free(ll_slist *list);

#endif
