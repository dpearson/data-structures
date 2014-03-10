//
//  cstr.h
//  Data Structures
//
//  Created by David Pearson on 3/3/14.
//  Copyright (c) 2014 David Pearson. All rights reserved.
//

#ifndef beale_cstr_h
#define beale_cstr_h

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	unsigned long length;
	unsigned long capacity;

	char *string;
} cstr;

cstr *cstr_new();

bool cstr_set_value(cstr *str, char *val);

bool cstr_cat(cstr *str, char *second);
bool cstr_cat_int(cstr *str, int val);

void cstr_free(cstr *str);

#endif
