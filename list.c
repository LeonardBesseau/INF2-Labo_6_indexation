#include "list.h"
#include <string.h>

/**
 * Swap memory of element
 */
#define swap(x, y) do \
   { unsigned char swap_temp[sizeof(x) == sizeof(y) ? (signed)sizeof(x) : -1]; \
     memcpy(swap_temp,&y,sizeof(x)); \
     memcpy(&y,&x,       sizeof(x)); \
     memcpy(&x,swap_temp,sizeof(x)); \
    } while(0)

typedef struct LinkedNode Node;

Node *createNode(Node *next, Node *prev, void *data);

void eraseNode(Node *m, void (*destroy)(void *));

Node *beginNode(const List *l);

Node *endNode(const List *l);

bool insertNode(Node *m, void *value);

void swapNode(Node *a, Node *b);


struct LinkedNode {
    Node *next;
    Node *prev;
    void *data;
};

struct LinkedList {
    Node *bfbl;
    size_t size;

    void (*destroy)(void *);

    int (*cmp)(const void *, const void *);

    void (*display)(const void *, FILE*);
};

Node *createNode(Node *next, Node *prev, void *data) {
    Node *output = malloc(sizeof(Node));
    if (output) {
        output->next = next;
        output->prev = prev;
        output->data = data;
        return output;
    } else {
        return NULL;
    }
}

void eraseNode(Node *m, void (*destroy)(void *)) {
    if (m) {
        m->prev->next = m->next;
        m->next->prev = m->prev;
        destroy(m->data);
        free(m);
    }
}

Node *beginNode(const List *l) {
    return l->bfbl->next;
}

Node *endNode(const List *l) {
    return l->bfbl;
}

bool insertNode(Node *m, void *value) {
    Node *prev = m->prev;
    Node *new = (Node *) createNode(m, prev, value);
    if (new) {
        prev->next = new;
        m->prev = new;
        return true;
    } else {
        return false;
    }
}

void swapNode(Node *a, Node *b) {
    if (a == b) {
        return;
    }
    Node *m1p = a->prev;
    Node *m1s = a->next;
    Node *m2p = b->prev;
    Node *m2s = b->next;

    swap(m1p->next, m2p->next);
    swap(a->next, b->next);
    swap(m1s->prev, m2s->prev);
    swap(a->prev, b->prev);


}


List *createEmptyList() {
    List *out = malloc(sizeof(List));
    if (out) {

        out->bfbl = createNode(NULL, NULL, NULL);

        if (out->bfbl) {
            out->destroy = NULL;
            out->cmp = NULL;
            out->display = NULL;
            out->size = 0;
            out->bfbl->next = out->bfbl;
            out->bfbl->prev = out->bfbl;
            return out;
        }
        //if bfbl creation failed release memory
        free(out);
    }
    return NULL;
}

void deleteList(List *l) {
    while (!isListEmpty(l)) {
        eraseNode(l->bfbl->next, l->destroy);
    }
    free(l->bfbl);
    free(l);
}

bool isListEmpty(const List *l) {
    return beginNode(l) == endNode(l);
}

size_t listSize(const List *l) {
    return l->size;
}

void *front(const List *l) {
    if (!isListEmpty(l)) {
        Node *n = beginNode(l);
        return n->data;
    }
    return NULL;
}

void *back(const List *l) {
    if (!isListEmpty(l)) {
        Node *n = endNode(l)->prev;
        return n->data;
    }
    return NULL;
}

void *getElement(List *l, const void *a) {
    Node *cur = beginNode(l);
    while (cur != endNode(l)) {
        if (!l->cmp(cur->data, a)) {
            return cur->data;
        }
        cur = cur->next;
    }

    return NULL;
}


bool pushFront(List *l, void *data) {
    bool result = insertNode(beginNode(l), data);
    l->size = result ? l->size + 1 : l->size;
    return result;
}

bool pushBack(List *l, void *data) {
    bool result = insertNode(endNode(l), data);
    l->size = result ? l->size + 1 : l->size;
    return result;
}

void pop_front(List *l) {
    if (!isListEmpty(l)) {
        eraseNode(beginNode(l), l->destroy);
        --l->size;
    }
}

void pop_back(List *l) {
    if (!isListEmpty(l)) {
        eraseNode(endNode(l)->prev, l->destroy);
        --l->size;
    }
}

bool insertInOrder(List *l, void *data, void **out) {
    Node *cur = beginNode(l);
    while (cur != endNode(l)) {
        int cmp = l->cmp(data,cur->data);
        if (cmp < 0) {
            bool result = insertNode(cur, data);
            l->size = result ? l->size + 1 : l->size;
            return result;
        } else if (cmp == 0) {
            *out = cur->data;
            return true;
        }
        cur = cur->next;
    }
    return pushBack(l, data);
}

void displayList(const List *l, bool separator, FILE* output) {
    Node *cur = beginNode(l);
    Node* end = endNode(l);
    bool loop = cur != end;
    while (loop) {
        l->display(cur->data, output);
        cur = cur->next;
        loop = cur != end;
        if (separator && loop){
            fprintf(output,", ");
        }
    }
    fprintf(output,"\n");
}

void sortList(List *l) {
    if (l->size < 2) {
        return;
    }
    Node *j = beginNode(l);
    const Node *end = endNode(l);

    while (j != end) {
        Node *iMin = j;
        Node *i = iMin->next;
        while (i != end) {
            if (l->cmp(i->data, iMin->data) < 0) {
                iMin = i;
            }
            i = i->next;
        }
        swapNode(iMin, j);
        j = iMin->next;
    }
}

void setCleanup(List *l, void (*destroy)(void *)) {
    l->destroy = destroy;
}


void setDisplay(List *l, void (*display)(const void *, FILE*)) {
    l->display = display;
}

void setCompare(List *l, int(*cmp)(const void *a, const void *b)) {
    l->cmp = cmp;
}