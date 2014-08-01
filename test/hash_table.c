/*
 *  hmaptests.c
 *  Data Structures
 *
 *  Created by David Pearson on 8/18/13.
 *  Copyright (c) 2013-2014 David Pearson. All rights reserved.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "hash_table.h"

bool hash_table_test() {
    hash_table *table = hash_table_new();
    
    if (table == NULL) {
        printf("ERROR: Could not create array\n");
        return false;
    }
    
    char *test_val_0 = "These are the times that try men's souls...";
    char *test_val_1 = "We hold these truths to be self-evident, that all men are created equal, that they are endowed by their Creator with certain unalienable Rights, that among these are Life, Liberty and the pursuit of Happiness.";
    char *test_val_2 = "Now, therefore, I, Gerald R. Ford, President of the United States, pursuant to the pardon power conferred upon me by Article II, Section 2, of the Constitution, have granted and by these presents do grant a full, free, and absolute pardon unto Richard Nixon for all offenses against the United States which he, Richard Nixon, has committed or may have committed or taken part in during the period from July (January) 20, 1969, through August 9, 1974.";
    
    hash_table_set(table, test_val_0, "test0", NULL);
    hash_table_set(table, test_val_1, "test1", NULL);
    hash_table_set(table, test_val_2, "another_test", NULL);

    char *value = hash_table_get(table, "test0");
    if (value != NULL && strcmp(value, test_val_0) != 0) {
        printf("ERROR: When reading hash table, expected \"%s\" but got \"%s\"\n", test_val_0, value);
        return false;
    }

    value = hash_table_get(table, "test1");
    if (value != NULL && strcmp(value, test_val_1) != 0) {
        printf("ERROR: When reading hash table, expected \"%s\" but got \"%s\"\n", test_val_1, value);
        return false;
    }

    value = hash_table_get(table, "another_test");
    if (value != NULL && strcmp(value, test_val_2) != 0) {
        printf("ERROR: When reading hash table, expected \"%s\" but got \"%s\"\n", test_val_2, value);
        return false;
    }

    hash_table_free(table);
    
    return true;
}