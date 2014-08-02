/*
 *  lltests.c
 *  Data Structures
 *
 *  Created by David Pearson on 6/3/12.
 *  Copyright (c) 2012-2014 David Pearson. All rights reserved.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "sll.h"
#include "dll.h"

bool sll_test() {
	ll_slist *list = sll_new();
	
	if (list == NULL) {
		printf("ERROR: Could not create list\n");
		return false;
	}
	
	char *val = "Testing...";
	char *val2 = "Another test...";
	
	sll_append(list, val, NULL);
	sll_insert(list, val2, 1, NULL);
	sll_insert(list, val, 2, NULL);
	sll_insert(list, val2, 3, NULL);
	
	char *ret = sll_get(list, 1);
	if (strcmp(ret, val2) != 0) {
		printf("ERROR: When reading linked list, expected %s but got %s", val2, ret);
		return false;
	}
	
	sll_remove(list, 1);
	
	ret = sll_get(list, 1);
	if (strcmp(ret, val) != 0) {
		printf("ERROR: When reading linked list, expected %s but got %s", val, ret);
		return false;
	}
	
	sll_free(list);
	
	return true;
}

bool dll_test() {
	ll_dlist *dlist = dll_new();
	
	if (dlist == NULL) {
		printf("ERROR: Could not create list\n");
		return false;
	}
	
	char *val = "Testing...";
	char *val2 = "Another test...";
	
	dll_append(dlist, val, NULL);
	dll_insert(dlist, val2, 1, NULL);
	dll_insert(dlist, val, 2, NULL);
	dll_insert(dlist, val2, 3, NULL);
	
	char *ret = dll_get(dlist, 1);
	if (strcmp(ret, val2) != 0) {
		printf("ERROR: When reading linked list, expected %s but got %s", val2, ret);
		return false;
	}
	
	dll_remove(dlist, 1);
	
	ret = dll_get(dlist, 1);
	if (strcmp(ret, val) != 0) {
		printf("ERROR: When reading linked list, expected %s but got %s", val, ret);
		return false;
	}
	
	dll_free(dlist);
	
	return true;
}
