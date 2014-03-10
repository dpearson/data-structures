//
//  dll.c
//  Data Structures
//
//  Created by David Pearson on 6/3/12.
//  Copyright (c) 2012-2014 David Pearson. All rights reserved.
//

#include "dll.h"

/* Public: Creates a new doubly-linked list.
 *
 * Returns the new linked list, or NULL if it couldn't be created.
 */
ll_dlist *dll_new() {
    ll_dlist *list = malloc(sizeof(ll_dlist));
    if (list == NULL) {
    	return NULL;
    }

    list->length = 0;
    list->first = NULL;
    list->last = NULL;

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
bool dll_set(ll_dlist *list, void *elem, int index, void (*release_function)(void *)) {
    if (index > list->length) {
        index = list->length;
    }

    ll_delement *e = malloc(sizeof(ll_delement));
    if (e == NULL) {
    	return false;
    }

    e->data = elem;
    e->release_function = release_function;

    list->length++;

    if (index == 0) {
        e->next = list->first;
        e->prev = NULL;

        list->first = e;

        if (list->length == 0) {
            list->last = e;
        }

        return true;
    }

    ll_delement *prev = list->first;
    int i = 1;

    while (i < index) {
        prev = prev->next;
        i++;
    }

    e->next = prev->next;
    prev->next = e;
    e->prev = prev;

    if (index >= list->length - 1) {
        list->last = e;
    }

	return true;
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
bool dll_append(ll_dlist *list, void *elem, void (*release_function)(void *)) {
	if (list != NULL) {
		return dll_set(list, elem, list->length, release_function);
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
void *dll_get(ll_dlist *list, int index) {
    if (index == 0) {
    	if (list->first != NULL) {
	        return list->first->data;
	    } else {
	    	return NULL;
	    }
    }

    if (index >= list->length || index < 0) {
        return NULL;
    }

    if (index <= list->length / 2) {
        ll_delement *e = list->first;
        int i = 0;

        while (i < index && e != NULL) {
            e = e->next;
            i++;
        }

        if (e != NULL) {
            return e->data;
        }

        return NULL;
    }

    ll_delement *e = list->last;
    int i = list->length - 2;

    while (i > index && e != NULL) {
        e = e->prev;
        i--;
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
void *_dll_element_clean_up(ll_delement *elem) {
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
void *dll_remove(ll_dlist *list, int index) {
    if (index >= list->length) {
        return NULL;
    }

    if (index == 0) {
        ll_delement *elem = list->first;

        if (elem != NULL) {
            list->first = elem->next;

            if (list->first != NULL) {
                list->first->prev = NULL;
            }

            list->length--;

            return _dll_element_clean_up(elem);
        }

        return NULL;
    }

    ll_delement *prev = list->first;

    for (int i = 1; i < index; i++) {
        prev = prev->next;
    }

    ll_delement *elem = prev->next;
    prev->next = elem->next;

    if (elem->next != NULL) {
        ll_delement *next = elem->next;
        next->prev = prev;
    } else {
        list->last = elem->prev;
    }

    list->length--;

    return _dll_element_clean_up(elem);
}

/* Public: Removes all elements from a linked list.
 *
 * list - The linked list to clear
 *
 * Returns nothing.
 */
void dll_clear(ll_dlist *list) {
    ll_delement *elem = list->first;
    while (elem != NULL) {
        ll_delement *next = elem->next;
        _dll_element_clean_up(elem);
        elem = next;
    }

    list->first = NULL;
    list->last = NULL;
    list->length = 0;
}

/* Public: Clears and frees a linked list.
 *
 * list - The linked list to release
 *
 * Returns nothing.
 */
void dll_free(ll_dlist *list) {
    dll_clear(list);

    free(list);
}
