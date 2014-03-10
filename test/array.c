//
//  arraytests.c
//  Data Structures
//
//  Created by David Pearson on 8/18/13.
//  Copyright (c) 2013-2014 David Pearson. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "array.h"
#include "pointer_array.h"

bool array_test() {
	array *arr = array_new(sizeof(double));

	if (arr == NULL) {
		printf("ERROR: Could not create array\n");
		return false;
	}

	double test_val_0 = 13.0;
	double test_val_5 = -1.0;
	double test_val_2 = 500.9;

	array_set(arr, &test_val_0, 0);
	array_set(arr, &test_val_5, 5);
	array_set(arr, &test_val_2, 2);

	for (int i = 0; i < arr->length; i++) {
		double array_val = *(double *)array_get(arr, i);
		if (i == 0 && array_val != test_val_0) {
			printf("ERROR: When reading array, expected %f but got %f\n", test_val_0, array_val);
			return false;
		} else if (i == 2 && array_val != test_val_2) {
			printf("ERROR: When reading array, expected %f but got %f\n", test_val_2, array_val);
			return false;
		} else if (i == 5 && array_val != test_val_5) {
			printf("ERROR: When reading array, expected %f but got %f\n", test_val_5, array_val);
			return false;
		}
	}

	array_free(arr);

	return true;
}

bool pointer_array_test() {
	pointer_array *arr = pointer_array_new(sizeof(double));

	if (arr == NULL) {
		printf("ERROR: Could not create array\n");
		return false;
	}

	char *test_val_0 = "This is a test";
	char *test_val_5 = "Another test";
	char *test_val_2 = "Hi";

	pointer_array_set(arr, test_val_0, 0);
	pointer_array_set(arr, test_val_5, 5);
	pointer_array_set(arr, test_val_2, 2);

	for (int i = 0; i < arr->length; i++) {
		char *array_val = (char *)pointer_array_get(arr, i);
		if (i == 0 && strcmp(array_val, test_val_0) != 0) {
			printf("ERROR: When reading array, expected %s but got %s\n", test_val_0, array_val);
			return false;
		} else if (i == 2 && strcmp(array_val, test_val_2) != 0) {
			printf("ERROR: When reading array, expected %s but got %s\n", test_val_2, array_val);
			return false;
		} else if (i == 5 && strcmp(array_val, test_val_5)) {
			printf("ERROR: When reading array, expected %s but got %s\n", test_val_5, array_val);
			return false;
		}
	}

	pointer_array_free(arr);

	return true;
}