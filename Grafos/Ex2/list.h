typedef struct list_ List;

List *list_create();
void list_add(List *list, short val);
void list_remove(List *list, short val);
void list_print(List *list);
void list_delete(List **list);