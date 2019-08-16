
/* return new empty edge */

struct edge *new_edge() {

	struct edge *aux = (struct edge *)malloc(sizeof(struct edge));
	
	aux -> label = NULL;
	aux -> end1 = NULL;
	aux -> end2 = NULL;
	aux -> type = NULL;
	aux -> p1 = NULL;
	aux -> p2 = NULL;
	aux -> next = NULL;
	
	aux -> d = INFINITY;
	aux -> h = INFINITY;
	aux -> t1 = INFINITY;
	aux -> t2 = INFINITY;
	aux -> cost1 = INFINITY;
	aux -> cost2 = INFINITY;
	
	return(aux);
}


/* dump edges, recursively */

void dump_edge(struct edge *aux) {
	
	if (aux != NULL) {
		printf ("%s, %s -> %s, %s\n", aux->label, aux->end1, aux->end2, aux->type);
		dump_edge(aux -> next);
	}
}


/* dump edges, recursively, including all calculated data */

void dump_edge_data(struct edge *aux) {
	
	if (aux != NULL) {
		printf ("%s, %s -> %s, %s :\td=%.2lf h=%.2lf t=%.2lf/%.2lf cost=%.2lf/%.2lf\n", aux->label, aux->end1, aux->end2, aux->type, aux->d, aux->h, aux->t1, aux->t2, aux->cost1, aux->cost2);
		dump_edge_data(aux -> next);
	}
}


/* free a edge, recursively */

void free_edge(struct edge *aux) {

	if (aux != NULL) {
		free_edge(aux->next);
		free(aux);
	}
}
