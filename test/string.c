//
//  test/string.c
//  Data Structures
//
//  Created by David Pearson on 3/10/14.
//  Copyright (c) 2014 David Pearson. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "cstr.h"

bool cstr_test() {
	cstr *str = cstr_new();

	if (str == NULL) {
		printf("ERROR: Could not create cstring\n");
		return false;
	}

	char *val0 = "This is just a test";
	char *val1 = "This is another test";
	char *val2 = malloc((strlen(val1) + 1) * sizeof(char));
	if (val2 == NULL) {
		printf("ERROR: Could not allocate memory\n");
		return false;
	}
	strcpy(val2, val1);

	cstr_set_value(str, val0);
	if (strcmp(str->string, val0) != 0) {
		printf("ERROR: When reading cstring, expected %s but got %s\n", val0, str->string);
		free(val2);
		return false;
	}

	cstr_set_value(str, val2);
	free(val2);
	if (strcmp(str->string, val1) != 0) {
		printf("ERROR: When reading cstring, expected %s but got %s\n", val1, str->string);
		return false;
	}

	cstr_cat(str, val0);
	if (strcmp(str->string, "This is another testThis is just a test") != 0) {
		printf("ERROR: When reading cstring, expected %s%s but got %s\n", val1, val0, str->string);
		return false;
	}

	cstr_cat_int(str, -5);
	if (strcmp(str->string, "This is another testThis is just a test-5") != 0) {
		printf("ERROR: When reading cstring, expected %s%s-5 but got %s\n", val1, val0, str->string);
		return false;
	}

	cstr_cat_int(str, 0);
	if (strcmp(str->string, "This is another testThis is just a test-50") != 0) {
		printf("ERROR: When reading cstring, expected %s%s-50 but got %s\n", val1, val0, str->string);
		return false;
	}

	cstr_free(str);

	return true;
}
