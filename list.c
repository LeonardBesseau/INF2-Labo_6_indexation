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

#include "list.h"

Node *createNode(Node *next, Node *prev, void *value);

Node *next(Node* current);

Node *prev(Node* current);

void* get(Node* node);

Node* beginNode(List* l);

Node* endNode(List* l);

bool insertNode(Node* m, void* value);

void erase(Node* m);

struct LinkedNode {
    Node *next;
    Node *prev;
    void *value;
};

struct LinkedList {
    Node *apad;
};


List *createEmptyList() {
    List *out = (List *) malloc(sizeof(List));
    if (out) {
        out->apad = createNode(NULL, NULL, NULL);
        out->apad->next = out->apad;
        out->apad->prev = out->apad;
        return out;
    } else {
        return NULL;
    }

}

Node *createNode(Node *next, Node *prev, void *value) {
    Node *output = (Node *) malloc(sizeof(Node));
    if (output) {
        output->next = next;
        output->prev = prev;
        output->value = value;
        return output;
    } else {
        return NULL;
    }
}

Node *next(Node* current){
    if (current){
        return current->next;
    } else{
        return current;
    }
}

Node *prev(Node* current){
    if (current){
        return current->prev;
    } else{
        return current;
    }
}

void* get(Node* node){
    if (node){
        return node->value;
    } else{
        return NULL;
    }
}

Node* beginNode(List* l){
    return l->apad->next;
}

Node* endNode(List *l){
    return l->apad;
}

bool insertNode(Node* m, void* value){
    Node *prev = m->prev;
    Node *new = (Node*) createNode(m, prev, value);
    if (new){
        prev->next = new;
        m->prev = new;
        return true;
    }else{
        return false;
    }
}

void erase(Node* m){
    if (m){
        m->prev->next = m->next;
        m->next->prev = m->prev;
        free(m);
    }
}

void deleteList(List* l){
    while (!isListEmpty(l)){
        erase(l->apad->next);
    }
    free(l->apad);
    free(l);
}

bool isListEmpty(List* l){
    return beginNode(l) == endNode(l);
}

bool appendList(List* l, void* value){
    insertNode(endNode(l), value);
}

void* listBegin(List* l){
    if (!isListEmpty(l)){
        return beginNode(l)->value;
    } else{
        return NULL;
    }
}
void* listLast(List* l){
    if (!isListEmpty(l)){
        return l->apad->prev->value;
    } else{
        return NULL;
    }
}



