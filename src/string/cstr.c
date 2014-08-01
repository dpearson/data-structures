/*
 *  cstr.c
 *  Data Structures
 *
 *  Created by David Pearson on 3/3/14.
 *  Copyright (c) 2014 David Pearson. All rights reserved.
 */

#include "cstr.h"

/* Public: Creates a new cstring.
 *
 * Returns the new string, or NULL if it couldn't be created.
 */
cstr *cstr_new() {
	unsigned long initial_capacity = 2;

	cstr *str = malloc(sizeof(cstr));
	if (str == NULL) {
		return NULL;
	}

	str->length = 0;
	str->capacity = initial_capacity;

	str->string = malloc(initial_capacity * sizeof(char));
	if (str->string == NULL) {
		free(str);
		
		return NULL;
	}

	str->string[0] = '\0';

	return str;
}

/* Private: Resizes a cstring.
 *
 * str - The cstring to be resized
 * target_capacity - The minimum number of characters that
 *                   should be present in the new cstring
 *                   (including the null terminator character);
 *                   the actual number may be greater
 *
 * Returns true if the resizing was successful;
 * otherwise false is returned, and the cstring referenced
 * by str is unchanged.
 */
bool _resize_string(cstr *str, unsigned long target_capacity) {
	size_t new_capacity = str->capacity * 2;
	while (new_capacity < target_capacity) {
		new_capacity *= 2;
	}

	char *new_string = realloc(str->string, new_capacity * sizeof(char));
	if (new_string == NULL) {
		return false;
	}

	str->string = new_string;
	str->capacity = new_capacity;

	return true;
}

/* Public: Sets the value of a cstring.
 *
 * str - The cstring that will hold the provided string value
 * val - The value to use, which will be copied into str and
 *       may be safely freed.
 *
 * Returns true if the value of str was successfully modified;
 * otherwise, false is returned, and the cstring referenced
 * by str is unchanged.
 */
bool cstr_set_value(cstr *str, char *val) {
	if (str == NULL || val == NULL) {
		return false;
	}

	unsigned long new_len = strlen(val);
	if (new_len + 1 > str->capacity) {
		if (!_resize_string(str, new_len + 1)) {
			return false;
		}
	}

	if (strcpy(str->string, val) != NULL) {
		str->length = new_len;
		return true;
	}

	return false;
}

/* Public: Concantenates a string onto this cstring
 *
 * str - The cstring that will be added to
 * second - The string to append onto the end of str,
 *          which will be copied into str and may be
 *          safely freed.
 *
 * Returns true if the value of str was successfully modified;
 * otherwise, false is returned, and the cstring referenced
 * by str is unchanged.
 */
bool cstr_cat(cstr *str, char *second) {
	if (str == NULL || second == NULL) {
		return false;
	}

	unsigned long new_len = str->length + strlen(second);
	if (new_len + 1 > str->capacity) {
		if (!_resize_string(str, new_len + 1)) {
			return false;
		}
	}

	if (strcat(str->string, second) != NULL) {
		str->length = new_len;
		return true;
	}

	return false;
}

/* Public: Concantenates an integer onto this cstring
 *
 * str - The cstring that will be added to
 * second - The integer to append onto the end of str,
 *          which will be copied into str and may be
 *          safely freed.
 *
 * Returns true if the value of str was successfully modified;
 * otherwise, false is returned, and the cstring referenced
 * by str is unchanged.
 */
bool cstr_cat_int(cstr *str, int val) {
	int digits = 2;
	if (val > 1) {
		digits = ceil(log10(val)) + 2;
	} else if (val < -1) {
		digits = ceil(log10(-1 * val)) + 3;
	} else if (val == 1) {
		return cstr_cat(str, "1");
	} else if (val == -1) {
		return cstr_cat(str, "-1");
	}

	char *new_string = malloc(digits * sizeof(char));
	if (new_string == NULL) {
		return false;
	}

	snprintf(new_string, digits, "%d", val);

	bool retVal = cstr_cat(str, new_string);

	free(new_string);

	return retVal;
}

/* Public: Gets the length of an existing cstring.
 *
 * str - The string to determine the length of
 *
 * Returns the length of the cstring.
 */
unsigned long cstr_length(cstr *str) {
	return str->length;
}

/* Public: Frees memory used by a cstring, including
 *         both data and information about the cstring.
 *
 * str - The cstring to free
 *
 * Returns nothing.
 */
void cstr_free(cstr *str) {
	free(str->string);
	free(str);
}
