/*
 *  pointer_array.h
 *  Data Structures
 *
 *  Created by David Pearson on 8/18/13.
 *  Copyright (c) 2013-2014 David Pearson. All rights reserved.
 */

#ifndef Data_Structures_pointer_array_h
#define Data_Structures_pointer_array_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	size_t bucket_size;
	unsigned int capacity;
	unsigned int length;

	void **data;
} pointer_array;

typedef struct {
	pointer_array *array;
	
	unsigned int current_index;
} pointer_array_iterator;

extern pointer_array *pointer_array_new();

extern bool pointer_array_set(pointer_array *arr, void *elem, unsigned int index);
extern bool pointer_array_append(pointer_array *arr, void *elem);

extern void *pointer_array_get(pointer_array *arr, unsigned int index);

extern pointer_array_iterator *pointer_array_iterator_get(pointer_array *arr);
extern bool pointer_array_iterator_has_previous(pointer_array_iterator *iter);
extern bool pointer_array_iterator_has_next(pointer_array_iterator *iter);
extern void *pointer_array_iterator_previous(pointer_array_iterator *iter);
extern void *pointer_array_iterator_next(pointer_array_iterator *iter);
extern void pointer_array_iterator_free(pointer_array_iterator *iter);

extern unsigned int pointer_array_length(pointer_array *arr);

extern void pointer_array_free(pointer_array *arr);

#endif
