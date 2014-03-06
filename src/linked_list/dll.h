//
//  dll.h
//  interpreter
//
//  Created by David Pearson on 6/3/12.
//  Copyright (c) 2012 David Pearson. All rights reserved.
//

#ifndef interpreter_dll_h
#define interpreter_dll_h

typedef struct {
    void *prev;
    void *data;
    void *next;
    void (*release_function)(void *);
} ll_delement;

typedef struct {
    unsigned int length;
    ll_delement *first;
    ll_delement *last;
} ll_dlist;

extern ll_dlist *dll_new();
extern void dll_add(ll_dlist *list, void *elem, int index, void (*release_function)(void *));
extern void *dll_get(ll_dlist *list, int index);
extern void *dll_remove(ll_dlist *list, int index);
extern void dll_clear(ll_dlist *list);
extern void dll_free(ll_dlist *list);


#endif
