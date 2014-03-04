//
//  array.c
//  Data Structures
//
//  Created by David Pearson on 7/30/13.
//  Copyright (c) 2013-2014 David Pearson. All rights reserved.
//

#include "array.h"

bool _resize_array(array **arr_ptr, unsigned int new_capacity);

/* Public: Creates a new array.
 *
 * bucket_size - The size of each bucket in the array,
 *               usually aquired by calling sizeof(type)
 *
 * Returns the new array, or NULL if it couldn't be created.
 */
array *array_new(size_t bucket_size) {
    unsigned int initial_capacity = 2;

    array *arr = malloc(sizeof(array));
	if (arr == NULL) {
		return NULL;
	}

    arr->bucket_size = bucket_size;
    arr->capacity = initial_capacity;
    arr->length = 0;

    arr->data = calloc(initial_capacity, bucket_size);
	if (arr->data == NULL) {
		free(arr);
		return NULL;
	}

    return arr;
}

/* Private: Resizes an array.
 *
 * arr_ptr - A pointer to the array to be resized
 * target_capacity - The minimum number of buckets that
 *                   should be present in the new array;
 *                   the actual number may be greater
 *
 * Returns true if the resizing was successful;
 * otherwise false is returned, and the array referenced
 * by arr_ptr is unchanged.
 */
bool _resize_array(array **arr_ptr, unsigned int target_capacity) {
	array *arr = *arr_ptr;

	unsigned int new_capacity = arr->capacity * 2;
	while (new_capacity < target_capacity) {
		new_capacity *= 2;
	}

	size_t old_size = arr->capacity * arr->bucket_size;
	size_t new_size = new_capacity * arr->bucket_size;
    void *new_block = realloc(arr->data, new_size);
	if (new_block == NULL) {
		return false;
	}

    if (new_size > old_size) {
        memset(new_block + old_size, 0, new_size - old_size);
    }

	arr->data = new_block;
	arr->capacity = new_capacity;

	return true;
}

/* Public: Sets the value of an element in an array.
 *
 * arr - The array to set the value in
 * elem - The element to store, the value of which will
 *        be copied into the array
 * index - The index to store elem at
 *
 * Returns true if the operation succeded; otherwise
 * false is returned.
 */
bool array_set(array *arr, void *elem, int index) {
    if (index - 1 > arr->capacity) {
		bool res = _resize_array(&arr, index + 1);
		if (!res) {
			return false;
		}
    }

    size_t offset = index * arr->bucket_size;
    memcpy(arr->data + offset, elem, arr->bucket_size);

    if (index + 1 > arr->length) {
        arr->length = index + 1;
    }

	return true;
}

/* Public: Appends an element to an array.
 *
 * arr - The array to which the element is to be appended
 * elem - The element to store, the value of which will
 *        be copied into the array
 *
 * Returns true if the operation succeeded; otherwise
 * false is returned.
 */
bool array_append(array *arr, void *elem) {
	int index = array_length(arr);
	return array_set(arr, elem, index);
}

/* Public: Gets an element from an array.
 *
 * arr - The array from which the element is to be
 *       gotten
 * index - The index to get the value of
 *
 * Returns the element at the specified index,
 * or NULL if it couldn't be accessed.
 */
void *array_get(array *arr, int index) {
	unsigned int length = array_length(arr);
	if (length <= index) {
		return NULL;
	}

    size_t offset = index * arr->bucket_size;
    return arr->data + offset;
}

/* Public: Gets the length of an existing array.
 *
 * arr - The array to determine the length of
 *
 * Returns the length of the array.
 */
unsigned int array_length(array *arr) {
	return arr->length;
}

/* Public: Frees memory used by an array, including
 *         both data and information about the array.
 *
 * arr - The array to free
 *
 * Returns nothing.
 */
void array_free(array *arr) {
    free(arr->data);
    free(arr);
}