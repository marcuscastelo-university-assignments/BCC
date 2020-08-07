typedef struct graph_ Graph;

Graph *graph_create(short n);
void graph_delete(Graph **g);

void graph_insert(Graph *g, short u, short v);
void graph_remove(Graph *g, short u, short v);

void graph_print(Graph *g);