//
//  hash_table.c
//  Data Structures
//
//  Created by David Pearson on 7/29/13.
//  Copyright (c) 2013-2014 David Pearson. All rights reserved.
//

#include "hash_table.h"

#define INITIAL_SIZE 4
#define BUCKET_SIZE sizeof(ll_dlist *)

typedef struct {
	  char *key;
	  void *value;
	  void (*release_function)(void *);
} hash_table_item;

unsigned int default_hash_function(char *key);
void _hash_table_item_free(hash_table_item *item);
bool _initialize_buckets(ll_dlist **array, size_t item_count);
bool _hash_table_grow(hash_table *table);
hash_table *_hash_table_new_with_size(unsigned int size, unsigned int (*hash_function)(char *));

/* Private: Hashes the provided key.
 *
 * key - The key to be hashed.
 *
 * Returns the key's hash.
 */
unsigned int default_hash_function(char *key) {
	  unsigned int hash = 0;

	  char *i = key;
	  while (*i != '\0') {
	      hash += 3 * (*i) - 19;
	      i++;
	  }

	  return hash;
}

/* Private: Frees an item in a hash_table.
 *
 * item - The item to free.
 *
 * Returns nothing.
 */
void _hash_table_item_free(hash_table_item *item) {
	  if (item->release_function != NULL) {
	      item->release_function(item->value);
	  }

	  free(item->key);
	  free(item);
}

/* Private: Initializes buckets for a hash table.
 *
 * array - The array of bucket lists to initialize.
 *         All contents are assumed to be NULL or freed.
 * item_count - The number of buckets to initialize.
 *
 * Returns the new array, or NULL if it couldn't be created.
 */
bool _initialize_buckets(ll_dlist **array, size_t item_count) {
	  for (int i = 0; i < item_count; i++) {
	      array[i] = dll_new();
		if (array[i] == NULL) {
			for (int j = 0; j < i; j++) {
				dll_free(array[j]);
			}

			return false;
		}
	  }

	return true;
}

/* Private: Increases the size of a hash table by a factor of 1.5.
 *          Copies all elements of the old table to a new one, then
 *          disposes of the old table.
 *
 * table - The table to resize.
 *
 * Returns true if the resizing succeeded; otherwise, false is
 * returned and the table is unchanged.
 */
bool _hash_table_grow(hash_table *table) {
	ll_dlist **list = table->items;

	unsigned int new_size = ceil(((double)table->bucket_count) * 1.5);
	unsigned int old_size = table->bucket_count;

	  ll_dlist **new_items = calloc(new_size, BUCKET_SIZE);
	if (new_items == NULL) {
		return false;
	}

	if (!_initialize_buckets(new_items, new_size)) {
		return false;
	}

	table->items = new_items;
	table->bucket_count = new_size;
	table->length = 0;

	  for (int i = 0; i < old_size; i++) {
		ll_dlist *bucket = list[i];
		if (bucket->length == 0) {
	          continue;
	      }

	      ll_delement *elem = bucket->first;

	      while (elem != NULL) {
	          hash_table_item *item = elem->data;
	          hash_table_set(table, item->value, item->key, item->release_function);

			free(item->key);
			free(item);

	          ll_delement *next = elem->next;

			free(elem);

			elem = next;
	      }
	  }

	free(list);

	return true;
}

/* Private: Creates a new hash table with the specified
 *          number of buckets and hash function.
 *
 * size - The number of buckets to be included in the new
 *        hash table.
 * hash_function - The hash function to use for the new
 *                 hash table.
 *
 * Returns the new hash table, or NULL if it couldn't be created.
 */
hash_table *_hash_table_new_with_size(unsigned int size, unsigned int (*hash_function)(char *)) {
	  hash_table *table = malloc(sizeof(hash_table));
	if (table == NULL) {
		return NULL;
	}

	  table->items = calloc(size, BUCKET_SIZE);
	if (table->items == NULL) {
		free(table);
		return NULL;
	}

	  table->bucket_count = size;
	  table->occupied_buckets = 0;
	  table->length = 0;
	  table->hash_function = hash_function;

	if (!_initialize_buckets(table->items, size)) {
		free(table->items);
		free(table);
		return NULL;
	}

	  return table;
}

/* Public: Creates a new hash table.
 *
 * Returns the new hash table, or NULL if it couldn't be created.
 */
hash_table *hash_table_new() {
	  return _hash_table_new_with_size(INITIAL_SIZE, &default_hash_function);
}

/* Public: Sets the value of a key in a hash table, resizing
 *         the table to maintain an appropriate load factor
 *         if necessary.
 *
 * table - The table to set the value in.
 * key - The key to set the value of.
 * elem - The element to set as the value of key.
 * release_function - A function to call when elem is removed
 *                    from the table, or NULL to call no function.
 *
 * Returns true if the element was added successfully;
 * otherwise, false is returned and the table is unchanged.
 */
bool hash_table_set(hash_table *table, void *elem, char *key, void (*release_function)(void *)) {
	  int index = table->hash_function(key) % table->bucket_count;
	  ll_dlist *bucket = table->items[index];
	  unsigned int item_count = bucket->length;

	  hash_table_item *item = NULL;
	  if (item_count != 0) {
	      hash_table_item *curr = NULL;
	      for (int i = 0; i < item_count; i++) {
	          curr = dll_get(bucket, i);
	          if (strcmp(key, curr->key) == 0) {
	              item = curr;
	              break;
	          }
	      }
	  } else {
	      table->occupied_buckets++;
	      if (((double)table->occupied_buckets) / ((double)table->bucket_count) >= 0.67) {
	          _hash_table_grow(table);
			return hash_table_set(table, elem, key, release_function);
	      }
	  }

	  if (item == NULL) {
	      item = malloc(sizeof(hash_table_item));
		if (item == NULL) {
			return false;
		}

	      item->key = malloc(strlen(key)*sizeof(char));
		if (item->key == NULL) {
			free(item);
			return false;
		}

	      item->key = strcpy(item->key, key);
	      item->value = elem;
	      item->release_function = release_function;

	      return dll_insert(bucket, item, item_count, (void (*)(void *))_hash_table_item_free);
	  } else {
	      item->value = elem;
	  }

	table->length++;

	return true;
}

/* Public: Gets the value of a key in a hash table.
 *
 * table - The table to get the value from.
 * key - The key to get the value of.
 *
 * Returns the value of key in table, or NULL if
 * the element couldn't be found.
 */
void *hash_table_get(hash_table *table, char *key) {
	  unsigned int index = table->hash_function(key) % table->bucket_count;
	  ll_dlist *bucket = table->items[index];
	  unsigned int item_count = bucket->length;

	  for (int i = 0; i < item_count; i++) {
	      hash_table_item *item = dll_get(bucket, i);
	      if (strcmp(key, item->key) == 0) {
	          return item->value;
	      }
	  }

	  return NULL;
}

/* Public: Clears and frees memory associated with a hash table.
 *
 * table - The table to free.
 *
 * Returns nothing.
 */
void hash_table_free(hash_table *table) {
	  for (int i = 0; i < table->bucket_count; i++) {
	      dll_clear(table->items[i]);
		dll_free(table->items[i]);
	  }

	  free(table->items);
	  free(table);
}
