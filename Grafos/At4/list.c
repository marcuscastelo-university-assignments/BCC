#include "list.h"
#include "edge.h"

#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

typedef struct lnode_ {
    Edge *edge;
    struct lnode_ *next;
} ListNode;

struct list_
{
    int size;
    ListNode *start, *end;
};

ListNode *_create_listnode(Edge *edge) {
    ListNode *ln = malloc(sizeof(ListNode));
    ln->edge = edge;
    ln->next = NULL;
}

List *list_create() {
    List *list = malloc(sizeof(List));
    list -> start = list -> end = NULL;
    list -> size = 0;
    return list;
}

void list_insert(List* q, Edge *edge) {
    if (q->end == NULL) q->start = q->end = _create_listnode(edge);
    else if (q->end == q->start) q->start->next = q->end = _create_listnode(edge);
    else { q->end->next = _create_listnode(edge); q->end = q->end->next; }
    q->size++;
}

int list_is_empty(List* q) {
    return q->start == NULL;
}

int list_get_size(List* q) {
    return q->size;
}

void list_delete(List** q_p) {
    #define q (*q_p)
    ListNode *to_delete = NULL;
    while (q->start != NULL) {
        to_delete = q->start;
        q->start = q->start->next;
        free(to_delete);
    }
    q->end = NULL;
    q->size = 0;
    free(q);
    q = NULL;
    #undef q
}

Edge *list_get(List *list, int index) {
    ListNode *lnode = list->start;
    for (int i = 0; i < index; i++)
    {
        if (lnode == NULL) {
            DP("list_get: index %d out of range\n", index);
            return NULL;
        }
        lnode = lnode -> next;
    }
    return lnode -> edge;
}