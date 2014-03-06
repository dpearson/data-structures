//
//  dll.c
//  interpreter
//
//  Created by David Pearson on 6/3/12.
//  Copyright (c) 2012 David Pearson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "dll.h"

ll_dlist *dll_new() {
    ll_dlist *list=malloc(sizeof(ll_dlist));
    list->length=0;
    list->first=NULL;
    list->last=NULL;
    
    return list;
}

void dll_add(ll_dlist *list, void *elem, int index, void (*release_function)(void *)) {
    if (index>list->length) {
        index=list->length;
    }
    
    ll_delement *e=malloc(sizeof(ll_delement));
    e->data=elem;
    e->release_function=release_function;
    
    list->length++;
    
    if (index==0) {
        e->next=list->first;
        e->prev=NULL;

        list->first=e;

        if (list->length==0) {
            list->last=e;
        }

        return;
    }
    
    ll_delement *prev=list->first;
    int i=1;
    
    while (i<index) {
        prev=prev->next;
        i++;
    }

    e->next=prev->next;
    prev->next=e;
    e->prev=prev;

    if (index>=list->length-1) {
        list->last=e;
    }
}

void *dll_get(ll_dlist *list, int index) {
    if (index==0) {
        return list->first->data;
    }

    if (index>=list->length) {
        return NULL;
    }

    if (index<=(list->length)/2) {
        ll_delement *e=list->first;
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

    ll_delement *e=list->last;
    int i=list->length-2;
    
    while (i>index) {
        e=e->prev;
        i--;
    }
    
    if (e!=NULL) {
        return e->data;
    }
    
    return NULL;
}

void *_dll_element_clean_up(ll_delement *elem) {
    void *data=NULL;
    
    if (elem->release_function!=NULL) {
        elem->release_function(elem->data);
    } else {
        data=elem->data;
    }
    
    free(elem);
    
    return data;
}

void *dll_remove(ll_dlist *list, int index) {
    if (index>=list->length) {
        return NULL;
    }

    if (index==0) {
        ll_delement *elem=list->first;

        if (elem!=NULL) {
            list->first=elem->next;

            if (list->first!=NULL) {
                list->first->prev=NULL;
            }

            list->length--;
            
            return _dll_element_clean_up(elem);
        }
        
        return NULL;
    }
    
    ll_delement *prev=list->first;

    for (int i=1; i<index; i++) {
        prev=prev->next;
    }
    
    ll_delement *elem=prev->next;
    prev->next=elem->next;

    if (elem->next!=NULL) {
        ll_delement *next=elem->next;
        next->prev=prev;
    } else {
        list->last=elem->prev;
    }
    
    list->length--;

    return _dll_element_clean_up(elem);
}

void dll_clear(ll_dlist *list) {
    ll_delement *elem=list->first;
    while (elem!=NULL) {
        ll_delement *next=elem->next;
        _dll_element_clean_up(elem);
        elem=next;
    }

    list->first=NULL;
    list->last=NULL;
    list->length=0;
}

void dll_free(ll_dlist *list) {
    dll_clear(list);
    
    free(list);
}