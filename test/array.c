/*
 *  arraytests.c
 *  Data Structures
 *
 *  Created by David Pearson on 8/18/13.
 *  Copyright (c) 2013-2014 David Pearson. All rights reserved.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "array.h"
#include "pointer_array.h"

int double_comparator(const void *one, const void *two) {
	return (*(double *)one) < (*(double *)two);
}

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

	int i;
	for (i = 0; i < arr->length; i++) {
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

	array_iterator *iter = array_iterator_get(arr);
	i = 0;
	while (array_iterator_has_next(iter)) {
		double array_val = *(double *)array_iterator_next(iter);
		if (i == 0 && array_val != test_val_0) {
			printf("ERROR: When iterating over array, expected %f but got %f\n", test_val_0, array_val);
			return false;
		} else if (i == 2 && array_val != test_val_2) {
			printf("ERROR: When iterating over array, expected %f but got %f\n", test_val_2, array_val);
			return false;
		} else if (i == 5 && array_val != test_val_5) {
			printf("ERROR: When iterating over array, expected %f but got %f\n", test_val_5, array_val);
			return false;
		}

		i++;
	}

	i = array_length(arr) - 1;

	while (array_iterator_has_previous(iter)) {
		double array_val = *(double *)array_iterator_previous(iter);
		if (i == 0 && array_val != test_val_0) {
			printf("ERROR: When iterating backward over array, expected %f but got %f\n", test_val_0, array_val);
			return false;
		} else if (i == 2 && array_val != test_val_2) {
			printf("ERROR: When iterating backward over array, expected %f but got %f\n", test_val_2, array_val);
			return false;
		} else if (i == 5 && array_val != test_val_5) {
			printf("ERROR: When iterating backward over array, expected %f but got %f\n", test_val_5, array_val);
			return false;
		}

		i--;
	}

	array_iterator_free(iter);

	double sorted[] = {500.900000, 13.000000, 0.000000, 0.000000, 0.000000, -1.000000};

	array_sort(arr, double_comparator);

	for (int i = 0; i < array_length(arr); i++) {
		double val = *(double *)array_get(arr, i);
		if (val != sorted[i]) {
			printf("ERROR: When reading sorted array, expected %f but got %f\n", sorted[i], val);
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

	int i;
	for (i = 0; i < arr->length; i++) {
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

	pointer_array_iterator *iter = pointer_array_iterator_get(arr);
	i = 0;
	while (pointer_array_iterator_has_next(iter)) {
		char *array_val = (char *)pointer_array_iterator_next(iter);
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

		i++;
	}

	i = pointer_array_length(arr) - 1;

	while (pointer_array_iterator_has_previous(iter)) {
		char *array_val = (char *)pointer_array_iterator_previous(iter);
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

		i++;
	}

	pointer_array_iterator_free(iter);
	pointer_array_free(arr);

	return true;
}
