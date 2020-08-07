#pragma once

#include "edge.h"

typedef struct list_ List;

List *list_create();

void list_insert(List* list, Edge *edge);
int list_is_empty(List*);
int list_get_size(List*);
Edge *list_get(List*, int index);

void list_delete(List**);

