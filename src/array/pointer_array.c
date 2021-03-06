/*
 *  pointer_array.c
 *  Data Structures
 *
 *  Created by David Pearson on 8/18/13.
 *  Copyright (c) 2013-2014 David Pearson. All rights reserved.
 */

#include "pointer_array.h"

bool _resize_pointer_array(pointer_array **arr_ptr, unsigned int target_capacity);

/* Public: Creates a new pointer array.
 *
 * Returns the new array, or NULL if it couldn't be created.
 */
pointer_array *pointer_array_new() {
	unsigned int initial_capacity = 2;

	pointer_array *arr = malloc(sizeof(pointer_array));
	if (arr == NULL) {
		return NULL;
	}

	arr->bucket_size = sizeof(void *);
	arr->capacity = initial_capacity;
	arr->length = 0;

	arr->data = calloc(initial_capacity, arr->bucket_size);
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
bool _resize_pointer_array(pointer_array **arr_ptr, unsigned int target_capacity) {
	pointer_array *arr = *arr_ptr;

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
 * elem - The element to store, a pointer to which will
 *        be copied into the array
 * index - The index to store elem at
 *
 * Returns true if the operation succeded; otherwise
 * false is returned.
 */
bool pointer_array_set(pointer_array *arr, void *elem, unsigned int index) {
	if (index >= arr->capacity) {
		bool res = _resize_pointer_array(&arr, index + 1);
		if (!res) {
			return false;
		}
	}

	arr->data[index] = elem;

	if (index + 1 > arr->length) {
		arr->length = index + 1;
	}

	return true;
}

/* Public: Appends an element to an array.
 *
 * arr - The array to which the element is to be appended
 * elem - The element to store, a pointer to which will
 *        be copied into the array
 *
 * Returns true if the operation succeeded; otherwise
 * false is returned.
 */
bool pointer_array_append(pointer_array *arr, void *elem) {
	return pointer_array_set(arr, elem, pointer_array_length(arr));
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
void *pointer_array_get(pointer_array *arr, unsigned int index) {
	if (index >= arr->length) {
		return NULL;
	}

	return arr->data[index];
}

/* Public: Gets an iterator for a pointer array.
 *
 * arr - The array for which to get an iterator
 *
 * Returns the iterator.
 */
pointer_array_iterator *pointer_array_iterator_get(pointer_array *arr) {
	pointer_array_iterator *iter = malloc(sizeof(pointer_array_iterator));
	if (iter == NULL) {
		return NULL;
	}

	iter->array = arr;
	iter->current_index = 0;

	return iter;
}

/* Public: Checks whether an iterator can step back
 * to and read another element without moving
 * the iterator.
 *
 * iter - The iterator to check
 *
 * Returns true if another element exists and the
 * iterator can be moved back.
 */
bool pointer_array_iterator_has_previous(pointer_array_iterator *iter) {
	return iter->current_index >= 1;
}

/* Public: Checks whether an iterator can advance
 * to and read another element without advancing
 * the iterator.
 *
 * iter - The iterator to check
 *
 * Returns true if another element exists and the
 * iterator can be advanced.
 */
bool pointer_array_iterator_has_next(pointer_array_iterator *iter) {
	return iter->current_index < iter->array->length;
}

/* Public: Moves an iterator back and returns the
 * previous element.
 *
 * iter - The iterator to use
 *
 * Returns the element at the previous index,
 * or NULL if it couldn't be accessed.
 */
void *pointer_array_iterator_previous(pointer_array_iterator *iter) {
	if (pointer_array_iterator_has_previous(iter)) {
		void *elem = pointer_array_get(iter->array, iter->current_index - 1);

		iter->current_index -= 1;

		return elem;
	}

	return NULL;
}

/* Public: Advances an iterator and returns the next element.
 *
 * iter - The iterator to use
 *
 * Returns the element at the next index,
 * or NULL if it couldn't be accessed.
 */
void *pointer_array_iterator_next(pointer_array_iterator *iter) {
	if (pointer_array_iterator_has_next(iter)) {
		void *elem = pointer_array_get(iter->array, iter->current_index);

		iter->current_index += 1;

		return elem;
	}

	return NULL;
}

/* Public: Frees an iterator. After calling this
 * method, the iterator should be considered unusable.
 *
 * iter - The iterator to free
 *
 * Returns nothing.
 */
void pointer_array_iterator_free(pointer_array_iterator *iter) {
	free(iter);
}

/* Public Sorts the contents of an array in place.
 *
 * arr - The array to sort
 * comparator - The function to use to compare elements
 *
 * Returns nothing.
 */
void pointer_array_sort(pointer_array *arr, int (*comparator)(const void *, const void *)) {
	qsort(arr->data, pointer_array_length(arr), arr->bucket_size, comparator);
}

/* Public: Gets the length of an existing array.
 *
 * arr - The array to determine the length of
 *
 * Returns the length of the array.
 */
unsigned int pointer_array_length(pointer_array *arr) {
	return arr->length;
}

/* Public: Frees memory used by an array, including
 *         both data and information about the array.
 *         Data pointed to by elements in the array
 *         should be manually freed before calling this
 *         function.
 *
 * arr - The array to free
 *
 * Returns nothing.
 */
void pointer_array_free(pointer_array *arr) {
	free(arr->data);
	free(arr);
}
