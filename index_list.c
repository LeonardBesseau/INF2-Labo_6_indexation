/* ---------------------------
Laboratoire :
Fichier : list.c
Auteur(s) : Besseau
Date : 02-06-2020

But :

Remarque(s) :

Compilateur : gcc version 7.4.0

--------------------------- */
#include <stdio.h>
#include <stdlib.h>

#include "index_list.h"

typedef struct LinkedIndexNode IndexNode;

IndexNode *createIndexNode(IndexNode *next, IndexNode *prev, int value);

IndexNode *nextIndex(IndexNode *current);

IndexNode *prevIndex(IndexNode *current);

int getIndex(IndexNode *node);

IndexNode *beginIndexNode(const IndexList *l);

IndexNode *endIndexNode(const IndexList *l);

bool insertNode(IndexNode *m, int value);

void eraseIndexNode(IndexNode *m);

struct LinkedIndexNode {
    IndexNode *next;
    IndexNode *prev;
    int value;
};

struct LinkedIndexList {
    IndexNode *apad;
    size_t size;
    int (*cmp)(const int *, const int *);
};


IndexList *createEmptyIndexList(int (*cmp)(const int *, const int *)) {
    IndexList *out = (IndexList *) malloc(sizeof(IndexList));
    if (out) {
        out->apad = createIndexNode(NULL, NULL, NULL);
        out->apad->next = out->apad;
        out->apad->prev = out->apad;
        out->cmp = cmp;
        out->size =0;
        return out;
    } else {
        return NULL;
    }

}

IndexNode *createIndexNode(IndexNode *next, IndexNode *prev, int value) {
    IndexNode *output = (IndexNode *) malloc(sizeof(IndexNode));
    if (output) {
        output->next = next;
        output->prev = prev;
        output->value = value;
        return output;
    } else {
        return NULL;
    }
}

IndexNode *nextIndex(IndexNode *current) {
    if (current) {
        return current->next;
    } else {
        return current;
    }
}

IndexNode *prevIndex(IndexNode *current) {
    if (current) {
        return current->prev;
    } else {
        return current;
    }
}

int getIndex(IndexNode *node) {
    if (node) {
        return node->value;
    }
}

IndexNode *beginIndexNode(const IndexList *l) {
    return l->apad->next;
}

IndexNode *endIndexNode(const IndexList *l) {
    return l->apad;
}

bool insertNode(IndexNode *m, int value) {
    IndexNode *prev = m->prev;
    IndexNode *new = (IndexNode *) createIndexNode(m, prev, value);
    if (new) {
        prev->next = new;
        m->prev = new;
        return true;
    } else {
        return false;
    }
}

void eraseIndexNode(IndexNode *m) {
    if (m) {
        m->prev->next = m->next;
        m->next->prev = m->prev;
        free(m);
    }
}

void deleteIndexList(IndexList *l) {
    while (!isIndexListEmpty(l)) {
        eraseIndexNode(l->apad->next);
    }
    free(l->apad);
    free(l);
}

bool isIndexListEmpty(const IndexList *l) {
    return beginIndexNode(l) == endIndexNode(l);
}

bool appendIndexList(IndexList *l, int value) {
    bool result = insertNode(endIndexNode(l), value);
    if (result){
        ++l->size;
        return result;
    } else{
        return false;
    }

}

int indexListBegin(const IndexList *l) {
    if (!isIndexListEmpty(l)) {
        return beginIndexNode(l)->value;
    }
    return -1;
}

int indexListLast(const IndexList *l) {
    if (!isIndexListEmpty(l)) {
        return l->apad->prev->value;
    }
    return -1;
}

int compareIndex(const int* lhs, const int* rhs){
    if(*lhs < *rhs){
        return -1;
    }else if(*lhs == *rhs){
        return 0;
    }{
        return 1;
    }
}

bool indexListContains(const IndexList *l, int value){
    IndexNode *cur = beginIndexNode(l);
    while (cur != endIndexNode(l)){
        if (value == cur->value){
            return true;
        }
        cur = cur->next;
    }
    return false;
}

void displayIndexList(const IndexList *l){
    IndexNode *cur = beginIndexNode(l);
    while (cur != endIndexNode(l)){
        printf("%d, ",cur->value);
        cur = cur->next;
    }
}

