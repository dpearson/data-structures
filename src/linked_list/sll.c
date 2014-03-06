//
//  sll.c
//  interpreter
//
//  Created by David Pearson on 6/1/12.
//  Copyright (c) 2012-2013 David Pearson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "sll.h"

ll_slist *sll_new() {
    ll_slist *list=malloc(sizeof(ll_slist));
    list->length=0;
    list->first=NULL;

    return list;
}

void sll_add(ll_slist *list, void *elem, int index, void (*release_function)(void *)) {
    if (index>list->length) {
        index=list->length;
    }

    ll_selement *e=malloc(sizeof(ll_selement));
    e->data=elem;
    e->release_function=release_function;

    list->length++;

    if (index==0) {
        e->next=list->first;
        list->first=e;
        return;
    }

    ll_selement *prev=list->first;
    int i=1;

    while (i<index) {
        prev=prev->next;
        i++;
    }

    e->next=prev->next;
    prev->next=e;
}

void *sll_get(ll_slist *list, int index) {
    if (index==0) {
        return list->first->data;
    }

    if (index>=list->length) {
        return NULL;
    }

    ll_selement *e=list->first;
    int i=0;
    
    while (i<index) {
        e=e->next;
        i++;
    }

    if (e!=NULL) {
        return e->data;
    }

    return NULL;
}

void *_sll_element_clean_up(ll_selement *elem) {
    void *data=NULL;
    
    if (elem->release_function!=NULL) {
        elem->release_function(elem->data);
    } else {
        data=elem->data;
    }
    
    free(elem);
    
    return data;
}

void *sll_remove(ll_slist *list, int index) {
    if (index>=list->length) {
        return NULL;
    }

    if (index==0) {
        ll_selement *elem=list->first;

        if (elem!=NULL) {
            list->first=elem->next;
            list->length--;

            return _sll_element_clean_up(elem);
        }

        return NULL;
    }

    ll_selement *prev=list->first;

    for (int i=1; i<index; i++) {
        prev=prev->next;
    }
    
    ll_selement *elem=prev->next;
    prev->next=elem->next;

    list->length--;

    return _sll_element_clean_up(elem);
}

void sll_clear(ll_slist *list) {
    ll_selement *elem=list->first;
    while (elem!=NULL) {
        ll_selement *next=elem->next;
        _sll_element_clean_up(elem);
        elem=next;
    }
    
    list->first=NULL;
    list->length=0;
}

void sll_free(ll_slist *list) {
    while (list->length>0) {
        sll_remove(list, 0);
    }

    free(list);
}