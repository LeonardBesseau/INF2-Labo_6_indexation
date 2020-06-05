#include "index_list.h"


typedef struct LinkedNode Node;


struct LinkedNode {
    Node *next;
    Node *prev;
    Type type;
    union {
        int value;
        Heading *heading;
    } data;
};

struct LinkedList {
    Node *apad;
    Type type;
    size_t size;
};


Node *createHeadingNode(Node *next, Node *prev, Heading *heading);

Node *createValueNode(Node *next, Node *prev, int value);

void eraseNode(Node *m);

Node *beginNode(const List* l);

Node *endNode(const List* l);

bool insertValueNode(Node *m, int value);

bool insertHeadingNode(Node *m, Heading *heading);

Node *createHeadingNode(Node *next, Node *prev, Heading *heading) {
    Node *output = (Node *) malloc(sizeof(Node));
    if (output) {
        output->next = next;
        output->prev = prev;
        output->type = HEADING;
        output->data.heading = heading;
        return output;
    } else {
        return NULL;
    }
}

Node *createValueNode(Node *next, Node *prev, int value) {
    Node *output = (Node *) malloc(sizeof(Node));
    if (output) {
        output->next = next;
        output->prev = prev;
        output->type = VALUE;
        output->data.value = value;
        return output;
    } else {
        return NULL;
    }
}

void eraseNode(Node *m) {
    if (m) {
        m->prev->next = m->next;
        m->next->prev = m->prev;
        if (m->type == HEADING) {
            free(m->data.heading);
        }
        free(m);
    }
}

Node *beginNode(const List* l){
    return l->apad->next;
}

Node *endNode(const List* l){
    return l->apad;
}

bool insertValueNode(Node *m, int value){
    Node *prev = m->prev;
    Node *new = (Node *) createValueNode(m, prev, value);
    if (new) {
        prev->next = new;
        m->prev = new;
        return true;
    } else {
        return false;
    }
}

bool insertHeadingNode(Node *m, Heading *heading){
    Node *prev = m->prev;
    Node *new = (Node *) createHeadingNode(m, prev, heading);
    if (new) {
        prev->next = new;
        m->prev = new;
        return true;
    } else {
        return false;
    }
}

List *createEmptyList(Type type) {
    List *out = (List *) malloc(sizeof(List));
    if (out) {
        if (type == VALUE) {
            out->apad = createValueNode(NULL, NULL, -1);
        } else {
            out->apad = createHeadingNode(NULL, NULL, NULL);
        }
        if (out->apad) {
            out->size = 0;
            out->apad->next = out->apad;
            out->apad->prev = out->apad;
            return out;
        }
        //if apad creation failed release memory
        free(out);
    }
    return NULL;
}

bool isListEmpty(const List *l) {
    return beginNode(l) == endNode(l);
}

size_t listSize(const List *l){
    return l->size;
}

int frontValue(const List *l){
    if (l->type == VALUE) {
        if (!isListEmpty(l)){
            Node *n = beginNode(l);
            return n->data.value;
        }
    }
    return -1;
}

int backValue(const List *l){
    if (l->type == VALUE) {
        if (!isListEmpty(l)){
            Node *n = endNode(l)->prev;
            return n->data.value;
        }
    }
    return -1;
}

Heading *frontHeading(const List *l){
    if (l->type == HEADING) {
        if (!isListEmpty(l)){
            Node *n = beginNode(l);
            return n->data.heading;
        }
    }
    return NULL;
}

Heading *backHeading(const List *l){
    if (l->type == VALUE) {
        if (!isListEmpty(l)){
            Node *n = endNode(l)->prev;
            return n->data.heading;
        }
    }
    return NULL;
}

bool pushValueFront(List *l, int value){
    bool result = insertValueNode(beginNode(l), value);
    l->size = result ? l->size+1: l->size;
    return result;
}

bool pushHeadingFront(List *l, Heading* heading){
    bool result = insertHeadingNode(beginNode(l), heading);
    l->size = result ? l->size+1: l->size;
    return result;
}

bool pushValueBack(List *l, int value){
    bool result = insertValueNode(endNode(l), value);
    l->size = result ? l->size+1: l->size;
    return result;
}

bool pushHeadingBack(List *l, Heading* heading){
    bool result = insertHeadingNode(endNode(l), heading);
    l->size = result ? l->size+1: l->size;
    return result;
}

void pop_front(List *l){
    if (!isListEmpty(l)){
        eraseNode(beginNode(l));
    }
}

void pop_back(List *l){
    if (!isListEmpty(l)){
        eraseNode(endNode(l));
    }
}

void deleteList(List* l){
    while (!isListEmpty(l)) {
        eraseNode(l->apad->next);
    }
    free(l->apad);
    free(l);
}


