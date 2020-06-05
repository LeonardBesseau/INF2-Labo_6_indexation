#include "list.h"
#include <stdio.h>
#include <string.h>


typedef struct LinkedNode Node;


struct LinkedNode {
    Node *next;
    Node *prev;
    Type type;
    union {
        int value;
        void *heading;
    } data;
};

struct LinkedList {
    Node *apad;
    Type type;
    size_t size;

    void (*destroy)(void *);

    int (*cmp)(const void *, const void *);

    void (*display)(const void *);
};


Node *createHeadingNode(Node *next, Node *prev, void *heading);

Node *createValueNode(Node *next, Node *prev, int value);

void eraseValueNode(Node *m);

void eraseHeadingNode(Node *m, void (*destroy)(void *));

Node *beginNode(const List *l);

Node *endNode(const List *l);

bool insertValueNode(Node *m, int value);

bool insertHeadingNode(Node *m, void *heading);

Node *createHeadingNode(Node *next, Node *prev, void *heading) {
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

void eraseValueNode(Node *m) {
    if (m) {
        m->prev->next = m->next;
        m->next->prev = m->prev;
        free(m);
    }
}

void eraseHeadingNode(Node *m, void (*destroy)(void *)) {
    if (m) {
        m->prev->next = m->next;
        m->next->prev = m->prev;
        destroy(m->data.heading);
        free(m);
    }
}

Node *beginNode(const List *l) {
    return l->apad->next;
}

Node *endNode(const List *l) {
    return l->apad;
}

bool insertValueNode(Node *m, int value) {
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

bool insertHeadingNode(Node *m, void *heading) {
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
            out->type = VALUE;
        } else {
            out->type = HEADING;
            out->apad = createHeadingNode(NULL, NULL, NULL);
        }
        if (out->apad) {
            out->destroy = NULL;
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

size_t listSize(const List *l) {
    return l->size;
}

int frontValue(const List *l) {
    if (l->type == VALUE) {
        if (!isListEmpty(l)) {
            Node *n = beginNode(l);
            return n->data.value;
        }
    }
    return -1;
}

int backValue(const List *l) {
    if (l->type == VALUE) {
        if (!isListEmpty(l)) {
            Node *n = endNode(l)->prev;
            return n->data.value;
        }
    }
    return -1;
}

void *frontHeading(const List *l) {
    if (l->type == HEADING) {
        if (!isListEmpty(l)) {
            Node *n = beginNode(l);
            return n->data.heading;
        }
    }
    return NULL;
}

void *backHeading(const List *l) {
    if (l->type == VALUE) {
        if (!isListEmpty(l)) {
            Node *n = endNode(l)->prev;
            return n->data.heading;
        }
    }
    return NULL;
}

bool pushValueFront(List *l, int value) {
    bool result = insertValueNode(beginNode(l), value);
    l->size = result ? l->size + 1 : l->size;
    return result;
}

bool pushHeadingFront(List *l, void *heading) {
    bool result = insertHeadingNode(beginNode(l), heading);
    l->size = result ? l->size + 1 : l->size;
    return result;
}

bool pushValueBack(List *l, int value) {
    bool result = insertValueNode(endNode(l), value);
    l->size = result ? l->size + 1 : l->size;
    return result;
}

bool pushHeadingBack(List *l, void *heading) {
    bool result = insertHeadingNode(endNode(l), heading);
    l->size = result ? l->size + 1 : l->size;
    return result;
}

void pop_front(List *l) {
    if (!isListEmpty(l)) {
        if (l->type == VALUE) {
            eraseValueNode(beginNode(l));
        } else {
            eraseHeadingNode(beginNode(l), l->destroy);
        }
        --l->size;
    }
}

void pop_back(List *l) {
    if (!isListEmpty(l)) {
        if (l->type == VALUE) {
            eraseValueNode(endNode(l)->prev);
        } else {
            eraseHeadingNode(endNode(l)->prev, l->destroy);
        }
        --l->size;
    }
}

void deleteList(List *l) {
    if (l->type == VALUE) {
        while (!isListEmpty(l)) {
            eraseValueNode(l->apad->next);
        }
    } else {
        while (!isListEmpty(l)) {
            eraseHeadingNode(l->apad->next, l->destroy);
        }
    }

    free(l->apad);
    free(l);
}

void setHeadingCleanup(List *l, void (*destroy)(void *)) {
    l->destroy = destroy;
}


void setDisplay(List *l, void (*display)(const void *)) {
    l->display = display;
}

void setComparaison(List* l, int(*cmp) (const void* a, const void* b)){
    l->cmp = cmp;
}


void displayList(List *l) {
    Node *cur = beginNode(l);
    while (cur != endNode(l)) {
        if (l->type == VALUE) {
            l->display(&cur->data.value);
        } else {
            l->display(cur->data.heading);
        }

        cur = cur->next;
    }
}

int compareInt(const void *a, const void *b) {
    const int *A = a, *B = b;
    return (*A > *B) - (*A < *B);
}

void displayInt(const void *a) {
    const int *A = a;
    printf("%d, ", *A);
}

void *getElement(List *l, const void *a) {
    if (l->type == VALUE) {
        Node *cur = beginNode(l);
        while (cur != endNode(l)) {
            if (!l->cmp(&cur->data.value, a)) {
                return &cur->data.value;
            }
            cur = cur->next;
        }
    } else {
        Node *cur = beginNode(l);
        while (cur != endNode(l)) {
            if (!l->cmp(cur->data.heading, a)) {
                return cur->data.heading;
            }
            cur = cur->next;
        }
    }
    return NULL;
}

