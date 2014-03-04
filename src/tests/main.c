//
//  main.c
//  Data Structures
//
//  Created by David Pearson on 7/29/13.
//  Copyright (c) 2013 David Pearson. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>

extern bool array_test();
extern bool pointer_array_test();

int main(int argc, const char * argv[])
{
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

    return 0;
}