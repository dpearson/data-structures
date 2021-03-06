/*
 *  array.c
 *  Data Structures
 *
 *  Created by David Pearson on 7/30/13.
 *  Copyright (c) 2013-2014 David Pearson. All rights reserved.
 */

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
bool array_set(array *arr, void *elem, unsigned int index) {
	if (index >= arr->capacity) {
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
void *array_get(array *arr, unsigned int index) {
	if (index >= arr->length) {
		return NULL;
	}

	unsigned int length = array_length(arr);
	if (length <= index) {
		return NULL;
	}

	size_t offset = index * arr->bucket_size;
	return arr->data + offset;
}

/* Public: Gets an iterator for an array.
 *
 * arr - The array for which to get an iterator
 *
 * Returns the iterator.
 */
array_iterator *array_iterator_get(array *arr) {
	array_iterator *iter = malloc(sizeof(array_iterator));
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
bool array_iterator_has_previous(array_iterator *iter) {
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
bool array_iterator_has_next(array_iterator *iter) {
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
void *array_iterator_previous(array_iterator *iter) {
	if (array_iterator_has_previous(iter)) {
		void *elem = array_get(iter->array, iter->current_index - 1);

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
void *array_iterator_next(array_iterator *iter) {
	if (array_iterator_has_next(iter)) {
		void *elem = array_get(iter->array, iter->current_index);

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
void array_iterator_free(array_iterator *iter) {
	free(iter);
}

/* Public Sorts the contents of an array in place.
 *
 * arr - The array to sort
 * comparator - The function to use to compare elements
 *
 * Returns nothing.
 */
void array_sort(array *arr, int (*comparator)(const void *, const void *)) {
	qsort(arr->data, array_length(arr), arr->bucket_size, comparator);
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
