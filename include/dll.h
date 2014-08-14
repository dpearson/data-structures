/*
 *  dll.h
 *  Data Structures
 *
 *  Created by David Pearson on 6/3/12.
 *  Copyright (c) 2012-2014 David Pearson. All rights reserved.
 */

#ifndef Data_Structures_dll_h
#define Data_Structures_dll_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ll_delement {
	/* A pointer to the previous element
	 */
	struct ll_delement *prev;
	
	/* A pointer to the previous element
	 */
	struct ll_delement *next;
	
	/* A pointer to the data for this element
	 */
	void *data;
	
	/* A descructor function for this element,
	 * which will be called when this element
	 * is removed from the list
	 */
	void (*release_function)(void *);
} ll_delement;

typedef struct {
	/* The list's head
	 */
	ll_delement *first;
	
	/* The list's tail
	 */
	ll_delement *last;
	
	/* The number of elements in the list
	 */
	unsigned int length;
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
