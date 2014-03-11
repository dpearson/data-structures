//
//  main.c
//  Data Structures
//
//  Created by David Pearson on 7/29/13.
//  Copyright (c) 2013-2014 David Pearson. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>

extern bool sll_test();
extern bool dll_test();
extern bool array_test();
extern bool pointer_array_test();
extern bool cstr_test();
extern bool hash_table_test();

int main(int argc, const char * argv[])
{
	if (sll_test()) {
		printf("SUCCESS: Singly linked list tests pass\n");
	} else {
		printf("Error: Singly linked list tests fail\n");
	}

	if (dll_test()) {
		printf("SUCCESS: Doubly linked list tests pass\n");
	} else {
		printf("Error: Doubly linked list tests fail\n");
	}

	if (array_test()) {
		printf("SUCCESS: Array tests pass\n");
	} else {
		printf("Error: Array tests fail\n");
	}

	if (pointer_array_test()) {
		printf("SUCCESS: Pointer array tests pass\n");
	} else {
		printf("Error: Pointer array tests fail\n");
	}

	if (cstr_test()) {
		printf("SUCCESS: C string tests pass\n");
	} else {
		printf("Error: C string tests fail\n");
	}

	if (hash_table_test()) {
        printf("SUCCESS: Hash table tests pass\n");
    } else {
        printf("Error: Hash table tests fail\n");
    }

	return 0;
}
