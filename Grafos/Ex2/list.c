#include "list.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct node_ {
    short val;
    struct node_ *next;
} Node;


struct list_
{
    Node *firstNode;
};



List *list_create() {
    List *list = malloc(sizeof(List));

    list->firstNode = NULL;

    return list;
    
}

Node *_createNode(int val) {
    Node *node = malloc(sizeof(Node));
    node -> val = val;
    node -> next = NULL;
    return node;
}

void list_add(List *list, short val) {
    Node *lastNode = NULL;
    Node *node = list->firstNode;
    while (node != NULL)
    {
        if (node->val == val) return;
        lastNode = node;
        node = node -> next;
    }
    
    if (lastNode == NULL)
        list->firstNode = _createNode(val);
    else 
        lastNode->next = _createNode(val);
}

void list_remove(List *list, short val) {
    Node *node = list->firstNode;
    Node *lastNode = NULL;
    while (node != NULL) {
        if (node -> val == val) {
            if (lastNode == NULL)
                list->firstNode = node->next;
            else
                lastNode->next = node->next;
            free(node);
            return;
        }
        lastNode = node;
        node = node -> next;
    }
    // printf("Node with value %d not found.\n", val);

}
void list_print(List *list) {
    Node *node = list->firstNode;
    while (node != NULL) {
        printf("%d ", node->val);
        node = node->next;
    }    
    printf("\n");
}

void delete(Node *node) {
    if (node == NULL) return; 
    Node *next = node->next;

    while (node != NULL)
    {
        next = node->next;
        free(node);
        node = next;
    }
    
}

void list_delete(List **list) {
    delete((*list)->firstNode);
    free(*list);
    *list = NULL;
}

