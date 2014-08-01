/*
 *  sll.c
 *  Data Structures
 *
 *  Created by David Pearson on 6/1/12.
 *  Copyright (c) 2012-2014 David Pearson. All rights reserved.
 */

#include "sll.h"

/* Public: Creates a new singly-linked list.
 *
 * Returns the new linked list, or NULL if it couldn't be created.
 */
ll_slist *sll_new() {
	ll_slist *list = malloc(sizeof(ll_slist));
	if (list == NULL) {
		return NULL;
	}

	list->length = 0;
	list->first = NULL;

	return list;
}

/* Public: Sets the value of an element in a linked list.
 *
 * list - The linked list to add the element to
 * elem - A pointer to the element to be added, which is
 *        not copied
 * index - The index to add the element at, which must
 *         not be greater than the length of the list
 * release_function - A function that frees memory allocated
 *                    for elem
 *
 * Returns true if the element was added successfully;
 * otherwise false is returned.
 */
bool sll_insert(ll_slist *list, void *elem, int index, void (*release_function)(void *)) {
	if (index > list->length) {
		index = list->length;
	}

	ll_selement *e = malloc(sizeof(ll_selement));
	if (e == NULL) {
		return false;
	}

	e->data = elem;
	e->release_function = release_function;

	list->length++;

	if (index == 0) {
		e->next = list->first;
		list->first = e;
		return true;
	}

	ll_selement *prev = list->first;
	int i = 1;

	while (i < index) {
		prev = prev->next;
		i++;
	}

	e->next = prev->next;
	prev->next = e;

	return true;
}

/* Public: Prepends an element to a linked list.
 *
 * list - The linked list to add the element to
 * elem - A pointer to the element to be added, which is
 *        not copied
 * release_function - A function that frees memory allocated
 *                    for elem
 *
 * Returns true if the element was added successfully;
 * otherwise false is returned.
 */
bool sll_prepend(ll_slist *list, void *elem, void (*release_function)(void *)) {
	if (list != NULL) {
	  return sll_insert(list, elem, 0, release_function);
	}

	return false;
}

/* Public: Appends an element to a linked list.
 *
 * list - The linked list to add the element to
 * elem - A pointer to the element to be added, which is
 *        not copied
 * release_function - A function that frees memory allocated
 *                    for elem
 *
 * Returns true if the element was added successfully;
 * otherwise false is returned.
 */
bool sll_append(ll_slist *list, void *elem, void (*release_function)(void *)) {
	if (list != NULL) {
		return sll_insert(list, elem, list->length, release_function);
	}

	return false;
}

/* Public: Gets the value of an element in a linked list.
 *
 * list - The linked list to get the element from
 * index - The index to get the element from, which must
 *         not be greater than the length of the list minus one
 *
 * Returns the element or NULL.
 */
void *sll_get(ll_slist *list, int index) {
	if (index == 0) {
		return list->first->data;
	}

	if (index >= list->length || index < 0) {
		return NULL;
	}

	ll_selement *e = list->first;
	int i = 0;

	while (i < index) {
		e = e->next;
		i++;
	}

	if (e != NULL) {
		return e->data;
	}

	return NULL;
}

/* Public: Cleans up memory associated with an element.
 *
 * elem - The element to free
 *
 * Returns the data stored in the element.
 */
void *_sll_element_clean_up(ll_selement *elem) {
	void *data = NULL;

	if (elem->release_function != NULL) {
		elem->release_function(elem->data);
	} else {
		data = elem->data;
	}

	free(elem);

	return data;
}

/* Public: Removes an element from a linked list.
 *
 * list - The linked list to remove the element from
 * index - The index to remove the element at, which must
 *         not be greater than the length of the list minus one
 *
 * Returns the element's data, or NULL if it was released or
 * not found.
 */
void *sll_remove(ll_slist *list, int index) {
	if (index >= list->length || index < 0) {
		return NULL;
	}

	if (index == 0) {
		ll_selement *elem = list->first;

		if (elem != NULL) {
			list->first = elem->next;
			list->length--;

			return _sll_element_clean_up(elem);
		}

		return NULL;
	}

	ll_selement *prev = list->first;

	int i = 1;
	for (i = 1; i < index; i++) {
		prev = prev->next;
	}

	ll_selement *elem = prev->next;
	prev->next = elem->next;

	list->length--;

	return _sll_element_clean_up(elem);
}

/* Public: Removes all elements from a linked list.
 *
 * list - The linked list to clear
 *
 * Returns nothing.
 */
void sll_clear(ll_slist *list) {
	ll_selement *elem = list->first;
	while (elem != NULL) {
		ll_selement *next = elem->next;
		_sll_element_clean_up(elem);
		elem = next;
	}

	list->first = NULL;
	list->length = 0;
}

/* Public: Clears and frees a linked list.
 *
 * list - The linked list to release
 *
 * Returns nothing.
 */
void sll_free(ll_slist *list) {
	while (list->length > 0) {
		sll_remove(list, 0);
	}

	free(list);
}
