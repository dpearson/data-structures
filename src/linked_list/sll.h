//
//  sll.h
//  interpreter
//
//  Created by David Pearson on 6/1/12.
//  Copyright (c) 2012 David Pearson. All rights reserved.
//

#ifndef interpreter_sll_h
#define interpreter_sll_h

typedef struct {
    void *data;
    void *next;
    void (*release_function)(void *);
} ll_selement;

typedef struct {
    unsigned int length;
    ll_selement *first; 
} ll_slist;

extern ll_slist *sll_new();
extern void sll_add(ll_slist *list, void *elem, int index, void (*release_function)(void *));
extern void *sll_get(ll_slist *list, int index);
extern void *sll_remove(ll_slist *list, int index);
extern void sll_clear(ll_slist *list);
extern void sll_free(ll_slist *list);

#endif
