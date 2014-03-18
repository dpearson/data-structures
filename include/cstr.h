//
//  cstr.h
//  Data Structures
//
//  Created by David Pearson on 3/3/14.
//  Copyright (c) 2014 David Pearson. All rights reserved.
//

#ifndef Data_Structures_cstr_h
#define Data_Structures_cstr_h

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

extern cstr *cstr_new();

extern bool cstr_set_value(cstr *str, char *val);

extern bool cstr_cat(cstr *str, char *second);
extern bool cstr_cat_int(cstr *str, int val);

extern unsigned int cstr_length(cstr *str);

extern void cstr_free(cstr *str);

#endif
