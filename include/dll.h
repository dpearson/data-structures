//
//  dll.h
//  Data Structures
//
//  Created by David Pearson on 6/3/12.
//  Copyright (c) 2012-2014 David Pearson. All rights reserved.
//

#ifndef Data_Structures_dll_h
#define Data_Structures_dll_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ll_delement {
	struct ll_delement *prev;
	void *data;
	struct ll_delement *next;
	void (*release_function)(void *);
} ll_delement;

typedef struct {
	unsigned int length;
	ll_delement *first;
	ll_delement *last;
} ll_dlist;

extern ll_dlist *dll_new();
extern bool dll_insert(ll_dlist *list, void *elem, int index, void (*release_function)(void *));
extern bool dll_prepend(ll_dlist *list, void *elem, void (*release_function)(void *));
extern bool dll_append(ll_dlist *list, void *elem, void (*release_function)(void *));
extern void *dll_get(ll_dlist *list, int index);
extern void *dll_remove(ll_dlist *list, int index);
extern void dll_clear(ll_dlist *list);
extern void dll_free(ll_dlist *list);

#endif
