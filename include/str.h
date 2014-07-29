//
//  cstr.h
//  Data Structures
//
//  Created by David Pearson on 3/3/14.
//  Copyright (c) 2014 David Pearson. All rights reserved.
//

#ifndef Data_Structures_str_h
#define Data_Structures_str_h

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	unsigned long length;
	unsigned long capacity;

	wchar_t *string;
} cstr;

cstr *str_new();

bool str_set_value(str *str, wchar_t *val);

bool str_cat(str *str, wchar_t *second);
bool str_cat_int(str *str, int val);

void str_free(str *str);

#endif
