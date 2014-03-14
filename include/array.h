//
//  array.h
//  Data Structures
//
//  Created by David Pearson on 7/30/13.
//  Copyright (c) 2013-2014 David Pearson. All rights reserved.
//

#ifndef Data_Structures_array_h
#define Data_Structures_array_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	size_t bucket_size;
	unsigned int capacity;
  unsigned int length;

  void *data;
} array;

extern array *array_new(size_t bucket_size);

extern bool array_set(array *arr, void *elem, unsigned int index);
extern bool array_append(array *arr, void *elem);

extern void *array_get(array *arr, unsigned int index);

extern unsigned int array_length(array *arr);

extern void array_free(array *arr);

#endif
